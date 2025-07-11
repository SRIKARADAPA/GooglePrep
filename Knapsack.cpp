#include <vector>
#include <iostream>
using namespace std;
int maxWeight(vector<int> &prices, vector<int> &costs, int weight){
    int n = prices.size();
    int maxCost = 0;
    vector<vector<int>> arr;
    for(int i=0;i<n;i++){
        arr.push_back({prices[i], costs[i]});
    }
    sort(arr.rbegin(), arr.rend());
    for(int i=0;i<n;i++){
        if(weight>=arr[i][1]){
            maxCost+=(arr[i][0]*arr[i][1]);
            weight-=(arr[i][1]);
        }
        else{
            maxCost+=(arr[i][0]*weight);
            break;
        }
    }
    return maxCost;
}
int main(){
    vector<int> prices;
    vector<int> costs;
    int weight;
    cout<<maxWeight(prices, costs, weight)<<" ";
}