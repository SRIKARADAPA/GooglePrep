#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;
int restrictedBfs(vector<vector<int>> &connections, unordered_set<int> &broken, int start, int destination){
    queue<pair<int,int>> nodes;
    nodes.emplace(start,0);
    unordered_set<int> visited;
    visited.insert(start);
    int ans = INT_MAX;
    while(!nodes.empty()){
        int node = nodes.front().first;
        int distance = nodes.front().second;
        nodes.pop();
        if(node == destination){
            ans = distance;
            break;
        }
        for(int i=0;i<connections[node].size(); i++){
            int neighbor = connections[node][i];
            if(visited.find(neighbor)==visited.end() && broken.find(neighbor)==broken.end()){
                visited.insert(neighbor);
                nodes.emplace(neighbor, distance+1);
            }
        }
    }
    return ans;
}
int freeBfs(vector<vector<int>> &connections, unordered_set<int> &broken, int start, int destination, int numNodes){
    if(start==destination){
        return 0;
    }
    queue<pair<int,int>> nodes;
    nodes.emplace(start,0);
    vector<int> distances(numNodes+1, INT_MAX);
    distances[start] = 0;
    while(!nodes.empty()){
        int node = nodes.front().first;
        int distance = nodes.front().second + (broken.find(node) == broken.end() ? 0 : 1);
        nodes.pop();
        for(int i=0;i<connections[node].size(); i++){
            int neighbor = connections[node][i];
            if(distances[neighbor]>distance){
                distances[neighbor] = distance;
                nodes.emplace(neighbor, distance);
            }
        }
    }
    return distances[destination];
}
int main(){
    vector<vector<int>> connections;
    connections.push_back({1,2});
    connections.push_back({2,3});
    connections.push_back({3,4});
    connections.push_back({4,6});
    connections.push_back({6,5});
    connections.push_back({5,7});
    connections.push_back({7,1});
    unordered_set<int> broken = {2,7,5,3};
    int start = 1;
    int destination = 4;
    int numNodes = connections.size();
   cout<<restrictedBfs(connections, broken, start, destination)<<" ";
   cout<<freeBfs(connections, broken, start, destination, numNodes)<<" ";
}