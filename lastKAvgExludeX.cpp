#include <vector>
#include <iostream>
#include <set>
using namespace std;
class AverageCalculator{
    public:
        int k;
        int x;
        deque<int> dq;
        multiset<int> ms;
        multiset<int> rest;
        int mainSum=0;
        int topSum=0;
        AverageCalculator(int K, int X){
            k=K;
            x=X;
        }
        void add(int num){
            dq.push_back(num);
            mainSum+=num;
            if(dq.size()>k){
                int popNum = dq.front();
                dq.pop_front();
                mainSum-=(popNum);
                if(ms.count(popNum)>0){
                    ms.erase(popNum);
                    topSum-=(popNum);
                    int val = *rest.rbegin();
                    rest.erase(val);
                    ms.insert(val);
                    topSum+=(val);
                }
                else{
                    rest.erase(popNum);
                }
            }
            ms.insert(num);
            topSum+=num;
            if(ms.size()>x){
                int val = *ms.begin();
                topSum-=val;
                ms.erase(val);
                rest.insert(val);
            }
        }
        double avg(){
            cout<<mainSum<<" "<<topSum<<" ";
            int dqSize = dq.size();
            int msSize = ms.size();
            return ((double)(mainSum - topSum))/((double)(dqSize - msSize));
        }
};
int main(){
    int K=10;
    int X=3;
    AverageCalculator calculator(K,X);
    calculator.add(10);
    calculator.add(9);
    calculator.add(8);
    calculator.add(7);
    calculator.add(6);
    calculator.add(5);
    calculator.add(4);
    calculator.add(3);
    calculator.add(2);
    calculator.add(1);
    calculator.add(3);
    calculator.add(4);
    cout<<calculator.avg()<<" ";
}