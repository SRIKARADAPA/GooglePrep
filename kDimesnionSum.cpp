#include <vector>
#include <iostream>
using namespace std;
int sum=0;
int getElement(vector<int> &indices){
    return 1;
}
void findSum(vector<int> &dimensions, int index){
    sum+=getElement(dimensions);
    for(int i=index;i<dimensions.size();i++){
        if(dimensions[i]==0){
            continue;
        }
        dimensions[i]--;
        findSum(dimensions, i);
        dimensions[i]++;
    }
    return;
}
int main(){
    vector<int> dimensions = {2,3,7,3};
    for(int i=0;i<dimensions.size();i++){
        dimensions[i]--;
    }
    findSum(dimensions,0);
    cout<<sum<<" ";
    return 0;
}