#include <vector>
#include <iostream>
using namespace std;
int maxGifts(vector<vector<int>> dayCosts){
    int ans = 0;
    priority_queue<int> bestGifts;
    int totalCost = 0;
    for(int i=0;i<dayCosts.size();i++){
        int day = dayCosts[i][0];
        int cost = dayCosts[i][1];
        if(day<cost){
            continue;
        }
        if(day-totalCost>=cost){
            bestGifts.push(cost);
            totalCost+=(cost);
        }
        else{
            if(!bestGifts.empty() && bestGifts.top()>cost){
                int topCost = bestGifts.top();
                bestGifts.pop();
                bestGifts.push(cost);
                totalCost+=(cost-topCost);
            }
        }
        int giftsSize = bestGifts.size();
        ans = max(ans, giftsSize);
    }
    return ans;
}
int main(){
    vector<vector<int>> dayCosts;
    dayCosts.push_back({1,2});
    dayCosts.push_back({3,2});
    dayCosts.push_back({5,3});
    dayCosts.push_back({6,2});
    dayCosts.push_back({7,2});
    int ans = maxGifts(dayCosts);
    cout<<ans<<" ";
}