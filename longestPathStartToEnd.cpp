#include <vector>
#include <iostream>
using namespace std;
int maxLength = 0;
void dfs(vector<vector<char>> &board, int row, int col, vector<vector<bool>> &visited, int dist){
    if(row<0 || row==board.size() || col<0 || col==board[0].size() || board[row][col] == '#' || visited[row][col]){
        return;
    }
    visited[row][col] = true;
    dist++;
    maxLength = max(maxLength, dist);
    dfs(board, row+1, col, visited, dist);
    dfs(board, row, col-1, visited, dist);
    dfs(board, row, col+1, visited, dist);
    visited[row][col] = false;
}
int main(){
    vector<vector<char>> board = {
        {'#', '.', '#', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '#'},
        {'#', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '#', '.', '#'}
    };
    int m = board.size();
    int n = board[0].size();
    for(int col=0;col<n;col++){
        if(board[0][col] == '.'){
            vector<vector<bool>> visited(m, vector<bool>(n,false));
            dfs(board, 0, col, visited, 0);
        }
    }
    cout<<maxLength<<" ";
}