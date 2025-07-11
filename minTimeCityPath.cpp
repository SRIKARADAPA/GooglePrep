#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

void buildGraph(unordered_map<int, vector<int>> &adjacencyList, vector<vector<int>> &edges){
    for(int i=0;i<edges.size();i++){
        adjacencyList[edges[i][0]].push_back(edges[i][1]);
        adjacencyList[edges[i][1]].push_back(edges[i][0]);
    }
    return;
}
int findMinTime(unordered_map<int, vector<int>> &adjacencyList, unordered_set<int> &blockedCities, int source, int destination){
    unordered_set<int> visited;
    visited.insert(source);
    queue<pair<int,int>> cities;
    cities.emplace(source,0);
    int ans = INT_MAX;
    while(!cities.empty()){
        int city = cities.front().first;
        int timeTaken = cities.front().second;
        cities.pop();
        if(city == destination){
            ans = timeTaken;
            break;
        }
        if(blockedCities.find(city)==blockedCities.end()){
            for(int i=0;i<adjacencyList[city].size();i++){
                int neighborCity = adjacencyList[city][i];
                if(visited.find(neighborCity)==visited.end()){
                    visited.insert(neighborCity);
                    cities.emplace(neighborCity, timeTaken+1);
                }
            }
        }
    }
    return ans;
}
int main(){
    vector<vector<int>> edges = {{1,2},{2,3},{3,4},{4,6},{6,5},{5,7},{7,1}};
    unordered_set<int> blockedCities = {2}; 
    int source = 1;
    int destination = 4;
    unordered_map<int, vector<int>> adjacencyList;
    buildGraph(adjacencyList, edges);
    cout<<findMinTime(adjacencyList, blockedCities, source, destination)<<" ";
}