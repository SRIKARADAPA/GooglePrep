#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <condition_variable>
#include <atomic>
#include <chrono>
using namespace std;

// Dummy CWFuture for illustration
class CWFuture {
public:
    bool done = false;
    int value = 0;
    bool fail = false;

    CWFuture(int result, bool failure = false) {
        value = result;
        fail = failure;
        thread([this]() {
            this_thread::sleep_for(chrono::milliseconds(100));
            done = true;
        }).detach();
    }

    bool IsDone() const { return done; }
    int Join() const {
        if (fail) throw runtime_error("Future failed");
        return value;
    }
};

// Dummy countWords function
CWFuture countWords(int machine_id, int doc_id) {
    return CWFuture(doc_id * 10, false); // simulate 10 words per doc_id
}

// Task representation
struct DocTask {
    int docId;
    int retryCount;
};

class WordCountSystem {
private:
    int n;
    queue<int> availableMachines;
    queue<DocTask> pendingDocs;
    queue<pair<int, CWFuture>> activeFutures;
    unordered_map<int, int> docToMachine;
    int maxRetries = 3;

    mutex mtx;
    condition_variable cv;
    atomic<bool> stopPolling{false};
    int totalWords = 0;

public:
    WordCountSystem(int n) : n(n) {
        for (int i = 0; i < n; ++i) {
            pendingDocs.push({i, 0});
            availableMachines.push(i);
        }
    }

    void assignTasks() {
        unique_lock<mutex> lock(mtx);
        // Wait until a machine becomes free or polling is stopped
        cv.wait_for(lock, chrono::milliseconds(200), [&]() {
            return !availableMachines.empty() || stopPolling;
        });

        while (!availableMachines.empty() && !pendingDocs.empty()) {
            DocTask task = pendingDocs.front(); pendingDocs.pop();
            int machine = availableMachines.front(); availableMachines.pop();

            CWFuture future = countWords(machine, task.docId);
            activeFutures.push({task.docId, future});
            docToMachine[task.docId] = machine;
        }
    }

    void pollingThread() {
        while (!stopPolling) {
            queue<pair<int, CWFuture>> tempQueue;

            {
                unique_lock<mutex> lock(mtx);
                while (!activeFutures.empty()) {
                    auto [docId, future] = activeFutures.front(); activeFutures.pop();

                    if (future.IsDone()) {
                        try {
                            int count = future.Join();
                            totalWords += count;
                            availableMachines.push(docToMachine[docId]);
                            cv.notify_one();
                        } catch (...) {
                            // Retry on failure
                            if (++retryCount[docId] <= maxRetries) {
                                pendingDocs.push({docId, retryCount[docId]});
                            } else {
                                cout << "Doc " << docId << " failed after retries.\n";
                            }
                            availableMachines.push(docToMachine[docId]);
                            cv.notify_one();
                        }
                    } else {
                        tempQueue.push({docId, future});
                    }
                }
                swap(activeFutures, tempQueue);
            }

            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }

    int totalWordsCount() {
        thread poller(&WordCountSystem::pollingThread, this);

        while (true) {
            {
                unique_lock<mutex> lock(mtx);
                if (pendingDocs.empty() && activeFutures.empty()) {
                    stopPolling = true;
                    cv.notify_all();
                    break;
                }
            }
            assignTasks();
        }

        poller.join();
        return totalWords;
    }

private:
    unordered_map<int, int> retryCount;
};
