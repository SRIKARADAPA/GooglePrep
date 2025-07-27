#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<pair<string,int>> wordsSpoken;
    int k;
    unordered_map<string,int> wordCountMap;
    for(int i=0;i<wordsSpoken.size();i++){
        wordCountMap[wordsSpoken[i].first]+=(wordsSpoken[i].second);
    }
    priority_queue<pair<int,string>,vector<pair<int,string>>, greater<pair<int,string>>> pq;
    for(auto it = wordCountMap.begin();it!=wordCountMap.end();it++){
        if(pq.size()<k){
            pq.push({it->second, it->first});
            continue;
        }
        if(!pq.empty() && it->second>pq.top().first){
            pq.pop();
            pq.push({it->second, it->first});
        }
    }
    vector<string> ans;
    while(!pq.empty()){
        ans.push_back(pq.top().second);
        pq.pop();
    }
    reverse(ans.begin(), ans.end());
}
