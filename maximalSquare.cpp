#include <vector>
#include <iostream>
using namespace std;

pair<pair<int,int>,int> maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        int ma = 0;
        int maX = 0;
        int maY = 0;
        for(int i=m-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                if(matrix[i][j]=='1'){
                    dp[i][j] = 1+min(dp[i+1][j], min(dp[i][j+1], dp[i+1][j+1]));
                }
                if(ma<dp[i][j]){
                    ma=dp[i][j];
                    maX = i;
                    maY = j;
                }
            }
        }
        return {{maX, maY}, ma};
}

int main(){
    vector<vector<char>> board = {
        {'0','1', '0', '0', '1'},
        {'1','0', '0', '1', '0'},
        {'0','1', '1', '1', '0'},
        {'1','1', '1', '1', '0'},
        {'1','1', '1', '1', '1'},
        {'0','0', '0', '0', '0'}};
    pair<pair<int,int>,int> ans = maximalSquare(board);
    cout<<"( "+ to_string(ans.first.first) + ", " + to_string(ans.first.second) + ") " + to_string(ans.second);
}