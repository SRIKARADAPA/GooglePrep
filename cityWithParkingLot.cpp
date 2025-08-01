#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector<vector<char>> city = {
        {'_','_','P'},
        {'_','_','_'},
        {'_','_','P'}
    };
    int m = city.size();
    int n = city[0].size();
    vector<vector<int>> distances(m, vector<int>(n,INT_MAX));
    queue<pair<pair<int,int>,int>> q;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(city[i][j] =='P'){
                distances[i][j] = 0;
                q.push({{i,j},0});
            }
        }
    }
    int ma = 0;
    while(!q.empty()){
        int i = q.front().first.first;
        int j = q.front().first.second;
        int dist = q.front().second;
        q.pop();
        ma = max(ma, dist);
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
    cout<<ma<<" ";
}