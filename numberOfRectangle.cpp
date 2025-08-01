#include <vector>
#include <iostream>
using namespace std;

struct Rectangle{
    int topLeftRow;
    int topLeftCol;
    int bottomRightRow;
    int bottomRightCol;
    int val;
    Rectangle(int a,int b,int c,int d,int e){
        topLeftRow = a;
        topLeftCol = b;
        bottomRightRow = c;
        bottomRightCol = d;
        val=e;
    }
};
void markVisited(vector<vector<bool>> &visited, int minRow, int minCol, int maxRow, int maxCol){
    // cout<<minRow<<" "<<maxRow<<" "<<minCol<<" "<<maxCol<<"\n";
    for(int i=minRow;i<maxRow;i++){
        for(int j=minCol; j<maxCol;j++){
            visited[i][j] = true;
        }
    }
    return;
}
void findMaxRect(vector<vector<int>> &grid, int i, int j, vector<vector<bool>> &visited, vector<Rectangle> &ans){
    int m = grid.size();
    int n = grid[0].size();
    int val = grid[i][j];
    int maxCol = n;
    int row = i;
    int col = j;
    while(row<m){
        if(grid[row][col]!=val){
            break;
        }
        while(col<maxCol && grid[row][col] == val){
            col++;
        }
        maxCol = min(maxCol, col);
        row++;
        col=j;
    }
    // cout<<i<<" "<<j<<" "<<row<<" "<<maxCol<<" ";
    ans.push_back(Rectangle(i,j,row,maxCol,grid[i][j]));
    markVisited(visited, i,j,row,maxCol);
    return;
}
int main(){
    vector<Rectangle> ans;
    vector<vector<int>> grid = {
        {1,2,2,3},
        {1,8,8,8},
        {1,3,3,8}
    };
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(!visited[i][j]){
                findMaxRect(grid,i,j,visited,ans);
            }
        }
    }
    for(int i=0;i<ans.size();i++){
        cout<<"Rectangle "+ to_string(i+1)+ "\n";
        for(int j=ans[i].topLeftRow;j<ans[i].bottomRightRow;j++){
            for(int k=ans[i].topLeftCol;k<ans[i].bottomRightCol;k++){
                cout<<ans[i].val<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
}