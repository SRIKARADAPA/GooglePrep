#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

class SongQueue {
private:
    list<string> songs; // Doubly linked list for O(1) insert/delete
    vector<list<string>::iterator> indexMap; // Map index to iterator

public:
    SongQueue(const vector<string>& initialSongs) {
        for (const auto& song : initialSongs) {
            songs.push_back(song);
        }

        // Build index map
        auto it = songs.begin();
        while (it != songs.end()) {
            indexMap.push_back(it++);
        }
    }

    void play(int k) {
        if (k < 1 || k > indexMap.size()) {
            cout << "Invalid song index" << endl;
            return;
        }

        auto it = indexMap[k - 1];
        string songToPlay = *it;
        cout << "Played: " << songToPlay << endl;

        // Remove from current position and push to end
        songs.erase(it);
        songs.push_back(songToPlay);

        // Rebuild indexMap
        indexMap.clear();
        auto iter = songs.begin();
        while (iter != songs.end()) {
            indexMap.push_back(iter++);
        }
    }

    void printQueue() {
        for (const auto& song : songs) {
            cout << song << " ";
        }
        cout << endl;
    }
};

int main() {
    vector<string> initialSongs = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    SongQueue queue(initialSongs);

    queue.play(3);  // Play C
    queue.printQueue();

    queue.play(5);  // Play F
    queue.printQueue();

    queue.play(2);  // Play B
    queue.printQueue();

    queue.play(8);  // Play C
    queue.printQueue();

    queue.play(10); // Play C again
    queue.printQueue();

    return 0;
}
