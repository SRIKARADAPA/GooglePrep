#include <vector>
#include<iostream>
using namespace std;
class streamKnapsack{
    public:
        int W;
        int currProfit = 0;
        int currCost = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> gems;
        streamKnapsack(int weight){
            W = weight;
        }
        void addGem(int price, int cost){
            gems.push({price,cost});
            currCost+=cost;
            currProfit+=(price*cost);
            while(!gems.empty() && currCost>W){
                int minPrice = gems.top().first;
                int minCost = gems.top().second;
                gems.pop();
                currCost-=(minCost);
                currProfit-=(minPrice*minCost);
                if(currCost<W){
                    gems.push({minPrice, W-currCost});
                    currProfit+=(minPrice*(W-currCost));
                    currCost = W;
                }
            }
            return;
        }
        int getMaxTotalWeight(){
            return currProfit;
        }
};
int main(){
    streamKnapsack obj(6);
    obj.addGem(2,3);
    cout<<obj.getMaxTotalWeight()<<" ";
    obj.addGem(1,3);
    cout<<obj.getMaxTotalWeight()<<" ";
    obj.addGem(4,2);
    cout<<obj.getMaxTotalWeight()<<" ";
    obj.addGem(5,3);
    cout<<obj.getMaxTotalWeight()<<" ";
    return 0;
}