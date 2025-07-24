#include <vector>
#include <iostream>
#include<set>
#include<unordered_set>
using namespace std;

struct Pos{
    int row;
    int col;
    bool operator<(const Pos &other) const{
        if(row==other.row){
            return col<other.col;
        }
        return row<other.row;
    }
    bool operator==(const Pos &other) const{
        return row==other.row && col==other.col;
    }
};
string bfs(vector<string> &maze){
    int m = maze.size();
    int n = maze[0].size();
    string ans = "No solution found";
    set<Pos> positions;
    Pos exitPos;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(maze[i][j] == '.'){
                positions.insert({i,j});
            }
            else if(maze[i][j] =='E'){
                positions.insert({i,j});
                exitPos = {i,j};
            }
        }
    }
    set<set<Pos>> visited;
    visited.insert(positions);
    queue<pair<set<Pos>, string>> q;
    q.push({positions, ""});
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    vector<string> directionStrings = {"U", "D", "L", "R"};
    while(!q.empty()){
        set<Pos> currentPositions = q.front().first;
        string currentPath = q.front().second;
        q.pop();
        if(currentPositions.size()==1 && *currentPositions.begin() == exitPos){
            ans = currentPath;
            break;
        }
        for(int i=0;i<4;i++){
            set<Pos> newPositions;
            for(Pos pos : currentPositions){
                int nextR = pos.row + directions[i][0];
                int nextC = pos.col + directions[i][1];
                if(nextR>=0 && nextR<m && nextC>=0 && nextC<n){
                    if(maze[nextR][nextC]!='#'){
                        newPositions.insert({nextR, nextC});
                    }
                    else{
                        newPositions.insert(pos);
                    }
                }else{
                    newPositions.insert(pos);
                }
            }
            if(!newPositions.empty() && visited.find(newPositions)==visited.end()){
                visited.insert(newPositions);
                q.push({newPositions, currentPath+directionStrings[i]});
            }
        }
    }
    return ans;
}
int main(){
    vector<string> maze = {
        "######",
        "#.#E.#",
        "#....#",
        "#.####"
    };
    cout<<bfs(maze)<<" ";
}