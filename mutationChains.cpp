#include <vector>
#include <iostream>
#include <unordered_set>
using namespace  std;

void buildGraph(vector<vector<int>> &adjacencyList, vector<vector<string>> &mutations, vector<int> &inDegree, unordered_set<int> &nodes){
    for(int i=0;i<mutations.size();i++){
        string s1 = mutations[i][0];
        string s2 = mutations[i][1];
        int size = s1.size();
        for(int j=0;j<size;j++){
            nodes.insert(s1[j]-'a');
            nodes.insert(s2[j]-'a');
            if(s1[j]!=s2[j]){
                adjacencyList[s1[j]-'a'].push_back(s2[j]-'a');
                inDegree[s2[j]-'a']++;
            }
        }
    }
}
vector<char> topSortBfs(vector<vector<int>> &adjacencyList,  vector<int> &inDegree, unordered_set<int> nodes){
    queue<pair<int,vector<char>>> q;
     vector<bool> visited(26);
    for(int i=0;i<26;i++){
        if(inDegree[i] == 0 && nodes.find(i)!=nodes.end()){
            visited[i] = true;
            vector<char> curr;
            curr.push_back('a'+i);
            q.emplace(i, curr);
        }
    }
    vector<char> ans;
    while(!q.empty()){
        int node = q.front().first;
        vector<char> curr = q.front().second;
        if(ans.size()<curr.size()){
            ans = curr;
        }
        q.pop();
        for(int i=0;i<adjacencyList[node].size();i++){
            int neighbor = adjacencyList[node][i];
            if(!visited[neighbor]){
                visited[neighbor] = true;
                vector<char> temp = curr;
                temp.push_back(neighbor + 'a');
                q.emplace(neighbor, temp);
            }
        }
    }
    return ans;
}
int main(){
    vector<vector<string>> mutations;
    mutations.push_back({"abb", "abc"});
    mutations.push_back({"xyz", "xxz"});
    mutations.push_back({"eee", "eee"});
    mutations.push_back({"aaaaac", "aabaag"});
    vector<vector<int>> adjacencyList(26);
    vector<int> inDegree(26,0);
    unordered_set<int> nodes;
    buildGraph(adjacencyList, mutations, inDegree, nodes);
    vector<char> ans = topSortBfs(adjacencyList, inDegree, nodes);
    for(char c : ans){
        cout<<c<<" ";
    }
}