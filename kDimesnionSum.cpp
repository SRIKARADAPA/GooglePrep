#include <vector>
#include <iostream>
using namespace std;
int sum=0;
int getElement(vector<int> &indices){
    for(int i=0;i<indices.size();i++){
        cout<<indices[i]<<" ";
    }
    cout<<"\n";
    return 1;
}
void findSum(vector<int> &dimensions){
    bool isFinished = false;
    int n = dimensions.size();
    vector<int> indices(n,0);
    while(!isFinished){
        sum+=getElement(indices);
        int i = n-1;
        while(i>=0){
            indices[i]++;
            if(indices[i]<dimensions[i]){
                break;
            }
            indices[i]=0;
            i--;
        }
        if(i<0){
            isFinished = true;
        }
    }
    return;
}
int main(){
    vector<int> dimensions = {2,2,4,4};
    findSum(dimensions);
    return 0;
}