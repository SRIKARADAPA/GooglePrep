#include <vector>
#include <iostream>
using namespace std;

void bfs(vector<vector<char>> &forest, vector<vector<int>> &distances){
    int m = forest.size();
    int n = forest[0].size();
    queue<pair<pair<int,int>,int>> q;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(forest[i][j] == 'L'){
                distances[i][j] = 0;
                q.push({{i,j},0});
            }
        }
    }
    while(!q.empty()){
        int i = q.front().first.first;
        int j = q.front().first.second;
        int dist = q.front().second;
        q.pop();
        if(i>0 && distances[i-1][j]>1+dist){
            distances[i-1][j] = 1+dist;
            q.push({{i-1,j},1+dist});
        }
        if(j>0 && distances[i][j-1]>1+dist){
            distances[i][j-1] = 1+dist;
            q.push({{i,j-1},1+dist});
        }
        if(i<m-1 && distances[i+1][j]>1+dist){
            distances[i+1][j] = 1+dist;
            q.push({{i+1,j},1+dist});
        }
        if(j<n-1 && distances[i][j+1]>1+dist){
            distances[i][j+1] = 1+dist;
            q.push({{i,j+1},1+dist});
        }
    }
    return;
}
int dijkstra(vector<vector<char>> &forest,vector<vector<int>> &distances){
    int m = forest.size();
    int n = forest[0].size();
    int startX;
    int startY;
    int endX;
    int endY;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(forest[i][j] == 'X'){
                startX = i;
                startY = j;
            }
            else if(forest[i][j] == 'C'){
                endX = i;
                endY = j;
            }
        }
    }
    priority_queue<pair<int,pair<int,int>>> pq;
    pq.push({distances[startX][startY], {startX, startY}});
    vector<vector<bool>> visited(m, vector<bool>(n,false));
    visited[startX][startY] = true;
    while(!pq.empty()){
        int maxDistanceInPath = pq.top().first;
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        pq.pop();
        if(i==endX && j==endY){
            return maxDistanceInPath;
        }
        if(i>0 && !visited[i-1][j]){
            visited[i-1][j] = true;
            pq.push({min(distances[i-1][j], maxDistanceInPath), {i-1,j}});
        }
        if(j>0 && !visited[i][j-1]){
            visited[i][j-1] = true;
            pq.push({min(distances[i][j-1], maxDistanceInPath), {i,j-1}});
        }
        if(i<m-1 && !visited[i+1][j]){
            visited[i+1][j] = true;
            pq.push({min(distances[i+1][j], maxDistanceInPath), {i+1,j}});
        }
        if(j<n-1 && !visited[i][j+1]){
            visited[i][j+1] = true;
            pq.push({min(distances[i][j+1], maxDistanceInPath), {i,j+1}});
        }
    }
    return -1;
}
int main(){
    vector<vector<char>> forest = {
        {'_','_','_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','C','_','_'},
        {'_','_','_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_','L','_'},
        {'_','_','_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','L','_','_','_','_'},
        {'_','_','_','_','_','_','_','L','_','_'},
        {'_','_','_','_','_','_','_','_','_','_'},
        {'L','_','_','_','X','_','_','_','_','_'}
    };
    int m = forest.size();
    int n = forest[0].size();
    vector<vector<int>> distances(m, vector<int>(n, INT_MAX));
    bfs(forest, distances);
    cout<<dijkstra(forest, distances);
}