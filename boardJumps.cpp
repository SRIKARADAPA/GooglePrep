#include <vector>
#include <iostream>
using namespace std;

int maxMovesWithNoRevisit(vector<vector<int>> &board){
    int m = board.size();
    int n = board[0].size();
    int ans = 0;
    queue<pair<pair<int,int>,int>> cells;
    cells.push({{0,0},0});
    while(!cells.empty()){
        int i = cells.front().first.first;
        int j = cells.front().first.second;
        int numMoves = cells.front().second;
        int val = board[i][j];
        ans = max(ans, numMoves);
        cells.pop();
        if(i>=val && board[i][j]>0){
            cells.push({{i-val, j},numMoves+1});
        }
        if(j>=val && board[i][j]>0){
            cells.push({{i, j-val},numMoves+1});
        }
        if(i<m-val && board[i][j]>0){
            cells.push({{i+val, j}, numMoves+1});
        }
        if(j<n-val && board[i][j]>0){
            cells.push({{i, j+val}, numMoves+1});
        }
        board[i][j] = -1;
    }
    return ans;
}
int main(){
    vector<vector<int>> board;
    board.push_back({2,0,8,4});
    board.push_back({0,1,1,0});
    board.push_back({3,0,0,5});
   cout<<maxMovesWithNoRevisit(board);
}
