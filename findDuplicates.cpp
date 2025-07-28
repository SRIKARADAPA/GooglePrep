#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool isEdge(vector<string> a, vector<string> b){
    return find(b.begin(), b.end(), a[1])!=b.end() || find(b.begin(), b.end(), a[2])!=b.end() || find(b.begin(), b.end(), a[3])!=b.end();
}
void buildGraph(unordered_map<string, vector<string>> &adjacencyList, vector<vector<string>> &elements){
    for(int i=0;i<elements.size();i++){
        for(int j=i+1;j<elements.size();j++){
            if(isEdge(elements[i], elements[j])){
                adjacencyList[elements[i][0]].push_back(elements[j][0]);
                adjacencyList[elements[j][0]].push_back(elements[i][0]);
            }
        }
    }
}
void dfs(unordered_map<string, vector<string>> &adjacencyList, string node, vector<string> &group, unordered_set<string> &visited){
    group.push_back(node);
    for(int i=0;i<adjacencyList[node].size();i++){
        string neighbor = adjacencyList[node][i];
        if(visited.find(neighbor)==visited.end()){
            visited.insert(neighbor);
            dfs(adjacencyList, neighbor, group, visited);
        }
    }
    return;
}
int main(){
    vector<vector<string>> elements = {{"id1", "p1", "p2", "p3"}, {"id2", "p1", "p4", "p5"}, {"id3", "p5", "p7", "p8"}};
    unordered_map<string, vector<string>> adjacencyList(elements.size());
    buildGraph(adjacencyList, elements);
    vector<vector<string>> groups;
    unordered_set<string> visited;
    for(int i=0;i<elements.size();i++){
        if(visited.find(elements[i][0])==visited.end()){
            vector<string> group;
            visited.insert(elements[i][0]);
            dfs(adjacencyList, elements[i][0], group, visited);
            groups.push_back(group);
        }
    }
    for(int i=0;i<groups.size();i++){
        for(int j=0;j<groups[i].size();j++){
            cout<<groups[i][j]<<" ";
        }
        cout<<"\n";
    }
}