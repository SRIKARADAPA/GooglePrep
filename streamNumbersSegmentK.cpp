#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;
class NumStream{
    public:
        int count=0;
        int k;
        unordered_map<int,int> numToSegmentMap;
        unordered_set<int> notContainedNums;
        int lastSeenNum = -1;
        NumStream(int K){
            k=K;
        }
        void addNumber(int num){
            int segment = count/k;
            if(count>0 && num!=lastSeenNum && notContainedNums.count(lastSeenNum)==0){
                cout<<lastSeenNum<<" ";
            }
            if(numToSegmentMap.count(num)==0){
                numToSegmentMap[num] = segment;
            }
            else{
                if(numToSegmentMap[num]!=segment){
                    notContainedNums.insert(num);
                    numToSegmentMap[num] = segment;
                }
            }
            count++;
            lastSeenNum = num;
        }
};
int main(){
    NumStream numStream(4);
    numStream.addNumber(1);
    numStream.addNumber(1);
    numStream.addNumber(2);
    numStream.addNumber(2);
    numStream.addNumber(2);
    numStream.addNumber(2);
    numStream.addNumber(3);
    numStream.addNumber(3);
    numStream.addNumber(3);
    numStream.addNumber(3);
    numStream.addNumber(3);
    numStream.addNumber(3);
    numStream.addNumber(4);
    numStream.addNumber(5);
    numStream.addNumber(5);
    numStream.addNumber(6);
    numStream.addNumber(6);
    numStream.addNumber(7);
    numStream.addNumber(7);
    numStream.addNumber(7);
    numStream.addNumber(8);
    numStream.addNumber(8);
    numStream.addNumber(8);
    numStream.addNumber(8);
}