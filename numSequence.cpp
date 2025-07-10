#include <vector>
#include <iostream>
#include<unordered_map>
#include<unordered_set>
using namespace std;

void buildGraph(vector<vector<int>> &sequences,  unordered_map<int,vector<int>> &adjacencyList, unordered_map<int,int> &inDegree, unordered_set<int> &uniqueNodes){
    for(int i=0;i<sequences.size();i++){
        vector<int> sequence = sequences[i];
        for(int j=0;j<sequence.size()-1;j++){
            adjacencyList[sequence[j]].push_back(sequence[j+1]);
            inDegree[sequence[j+1]]++;
            uniqueNodes.insert(sequence[j]);
        }
        uniqueNodes.insert(sequence[sequence.size()-1]);
    }
    return;
}
bool topSort(unordered_map<int, vector<int>> &adjacencyList,  unordered_map<int,int> &inDegree, unordered_set<int> uniqueNodes){
    queue<int> nodes;
    int totalNodes = uniqueNodes.size();
    int processedNodes = 0;
    for(auto node: uniqueNodes){
        if(inDegree.count(node)==0){
            nodes.push(node);
        }
    }
    while(!nodes.empty()){
        int node = nodes.front();
        nodes.pop();
        processedNodes++;
        for(int i=0;i<adjacencyList[node].size();i++){
            int neighbor = adjacencyList[node][i];
            inDegree[neighbor]--;
            if(inDegree[neighbor]==0){
                nodes.push(neighbor);
            }
        }
    }
    return processedNodes == totalNodes;
}
int main(){
    vector<vector<int>> sequences;
    vector<int> sequence1 = {1,6,4};
    vector<int> sequence2 = {4,1};
    sequences.push_back(sequence1);
    sequences.push_back(sequence2);
    unordered_map<int,int> inDegree;
    unordered_map<int,vector<int>> adjacencyList;
    unordered_set<int> uniqueNodes;
    buildGraph(sequences, adjacencyList, inDegree, uniqueNodes);
    bool ans = topSort(adjacencyList, inDegree, uniqueNodes);
    cout<<ans<<" ";
    return 0;
}