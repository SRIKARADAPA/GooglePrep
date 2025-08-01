#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

void dfs(unordered_map<int, unordered_set<int>> &mp, int currSum, int sum, vector<vector<int>> &ans, vector<int> curr){
    if(currSum>sum){
        return;
    }
    if(currSum == sum){
        if(mp[curr[curr.size()-1]].count(curr[1])>0){
             ans.push_back(curr);
        }
        return;
    }
    int lastValue = curr[curr.size()-1];
    unordered_set<int> allowedNotes = mp[lastValue];
    for(int i: allowedNotes){
        curr.push_back(i);
        dfs(mp, currSum+i, sum, ans, curr);
        curr.pop_back();
    }
    return;
}
int main(){
    vector<int> noteValues = {1,2,3};
    noteValues.insert(noteValues.begin(),0);
    vector<unordered_set<int>> transitions = {{2,3}, {1}, {1}};
    transitions.insert(transitions.begin(), {1,2,3});
    int sum = 12;
    int n = noteValues.size();
    unordered_map<int, unordered_set<int>> mp;
    vector<vector<int>> ans;
    for(int i=0;i<n;i++){
       mp[noteValues[i]] = transitions[i];
    }
    dfs(mp,0,sum,ans,{0});
    for(int i=0;i<ans.size();i++){
        for(int j=1;j<ans[i].size();j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<"\n";
    }
}