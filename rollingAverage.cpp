#include <vector>
#include <iostream>
using namespace std;
class AverageCalculator{
    public:
        int k;
        int totalLatency;
        deque<int> latencies;
    AverageCalculator(int K){
        k = K;
    }
    void addLatency(int latency){
        latencies.push_back(latency);
        totalLatency+=latency;
        if(latencies.size()>k){
            totalLatency-=(latencies.front());
            latencies.pop_front();
        }
    }
    int getAverage(){
        return totalLatency/k;
    }
};
int main(){
    AverageCalculator calculator(5);
    calculator.addLatency(50);
    calculator.addLatency(60);
    calculator.addLatency(70);
    calculator.addLatency(50);
    calculator.addLatency(100);
    calculator.addLatency(10);
    cout<<calculator.getAverage()<<" ";
    calculator.addLatency(120);
    cout<<calculator.getAverage()<<" ";
}