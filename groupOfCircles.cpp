#include <vector>
#include <iostream>
using namespace std;

bool isAdjacent(vector<int> c1, vector<int> c2){
    return pow(abs(c1[0]-c2[0]),2) + pow(abs(c1[1]-c2[1]),2) <= pow(abs(c1[2]+c2[2]),2);
}
bool bfs(vector<vector<int>> &circles){
    int n = circles.size();
    queue<vector<int>> q;
    q.push(circles[0]);
    vector<bool> visited(n, false);
    visited[0] = true;
    int count=1;
    while(!q.empty()){
        vector<int> circle = q.front();
        q.pop();
        for(int i=0;i<n;i++){
            if(!visited[i] && isAdjacent(circle, circles[i])){
                visited[i] = true;
                q.push(circles[i]);
                count++;
            }
        }
    }
    return count==n;
}
int main(){
    vector<vector<int>> circles = {{0,0,2}, {4,0,2}, {2,2,3}};
    cout<<bfs(circles)<<" ";
}