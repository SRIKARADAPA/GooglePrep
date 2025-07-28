#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if(n==1){
        return intervals;
    }
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    int left = 0;
    int right = 0;
    while(right<n){
        int start = intervals[left][0];
        int end = intervals[left][1];
        while(right<n && intervals[right][0]<=end){
            end = max(end, intervals[right][1]);
            right++;
        }
        ans.push_back({start, end});
        left = right;
    }
    return ans;
}

int main(){
    vector<vector<int>> intervals = {{1,2}, {4,7}, {5,8}};
    vector<vector<int>> mergedIntervals = merge(intervals);
    int maxDay = 10;
    vector<int> freeDays;
    for(int i=1;i<mergedIntervals[0][0];i++){
        freeDays.push_back(i);
    }
    int n = mergedIntervals.size();
    for(int i=0;i<n-1;i++){
        for(int j=mergedIntervals[i][1]+1;j<mergedIntervals[i+1][0];j++){
            freeDays.push_back(j);
        }
    }
    for(int i=mergedIntervals[mergedIntervals.size()-1][1]+1;i<=maxDay;i++){
        freeDays.push_back(i);
    }
    for(int i=0;i<freeDays.size();i++){
        cout<<freeDays[i]<<" ";
    }
}