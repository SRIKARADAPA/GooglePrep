#include <vector>
#include <iostream>
using namespace std;

bool binarySearch(vector<int> &v, int index, int val){
    int left = 0;
    int right = index;
    int ans = -1;
    while(left<=right){
        int mid = (left+right)/2;
        if(v[mid]<val){
            ans = mid;
            left=mid+1;
        }
        else{
            right = mid-1;
        }
    }
    return ans;
}
int findScore(vector<vector<int>> &arr, int i, int j){
    vector<int> v1 = arr[i];
    vector<int> v2 = arr[j];
    int n = v1.size();
    int p1 = 0;
    int index = n-1;
    for(int i=n-1;i>=0;i--){
        index = binarySearch(v2, index, v1[i]);
        if(index==-1){
            break;
        }
        p1+=(index+1);
    }
    return p1;
}
int main(){
    vector<vector<int>> arr = {{1,2,3,4}, {3,4,5,6}, {6,7,8,9}, {4,5,6,7}};
    int n = arr.size();
    for(int i=0;i<n;i++){
        sort(arr[i].begin(), arr[i].end());
    }
    vector<int> scores(n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j){
                int score = findScore(arr, i, j);
                scores[i]+=(score);
            }
        }
    }
    int winner = 0;
    int winningScore = scores[0];
    for(int i=1;i<n;i++){
        if(scores[i]>winningScore){
            winningScore = scores[i];
            winner = i;
        }
    }
    cout<<winner<<" ";
}