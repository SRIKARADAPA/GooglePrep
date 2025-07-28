#include <vector>
#include <iostream>
using namespace std;

int main(){
    int m = 3;
    int n = 4;
    vector<vector<int>> dp(m, vector<int>(n,0));
    dp[m-1][0] = 1;
    for(int i=1;i<n;i++){
        for(int j=m-1;j>=0;j--){
            if(i>0 && j>0){
                dp[j][i]+=(dp[j-1][i-1]);
            }
            if(j>0){
                dp[j][i]+=(dp[j][i-1]);
            }
            if(j<m-1 && i>0){
                dp[j][i]+=(dp[j+1][i-1]);
            }
        }
    }
    cout<<dp[m-1][n-1]<<" ";
}