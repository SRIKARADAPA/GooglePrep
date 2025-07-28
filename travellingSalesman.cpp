#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector<int> cost1 = {3,7,2,100};
    vector<int> cost2 = {10,1,5,1};
    int n = cost1.size();
    int val1 = cost1[0];
    int val2 = cost2[0];
    int travelCost = 2;
    for(int i=1;i<n;i++){
        int tempVal1 = val1;
        val1 = max(val2 + cost1[i] - travelCost, val1 + cost1[i]);
        val2 = max(val2 + cost2[i], tempVal1 + cost2[i] - travelCost);
    }
    cout<<max(val1,val2)<<" ";
}