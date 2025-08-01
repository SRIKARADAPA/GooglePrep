#include <vector>
#include <iostream>
using namespace std;

double findDistance(vector<int> p1, vector<int> p2){
    return pow(pow(abs(p1[0]-p2[0]),2) + pow(abs(p1[1]-p2[1]),2),0.5);
}
void buildGraph(vector<vector<int>> &adjacencyList, vector<vector<int>> &routers, int range){
    int n = routers.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double dist = findDistance(routers[i], routers[j]);
            if(dist<=range){
                adjacencyList[i].push_back(j);
                adjacencyList[j].push_back(i);
            }
        }
    }
    return;
}
bool dfs(vector<vector<int>> &adjacencyList, int node, int destination, vector<bool> &visited){
    if(node==destination){
        return true;
    }
    for(int i=0;i<adjacencyList[node].size();i++){
        int neighbor = adjacencyList[node][i];
        if(!visited[neighbor]){
            visited[neighbor] = true;
            if(dfs(adjacencyList,neighbor, destination, visited)){
                return true;
            }
        }
    }
    return false;
}
int main(){
    vector<vector<int>> routers = {{0,0}, {0,8}, {0,17}, {11,0}};
    int n = routers.size();
    int source = 0;
    int destination = 3;
    int range = 10;
    vector<vector<int>> adjacencyList(n);
    buildGraph(adjacencyList, routers, range);
    vector<bool> visited(n,false);
    visited[source] = true;
    cout<<dfs(adjacencyList, source, destination, visited);
}