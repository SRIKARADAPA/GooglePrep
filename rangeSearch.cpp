#include <vector>
#include <iostream>
using namespace std;
int lowerBound(vector<vector<double>> ranges, double query){
    int left = 0;
    int right = ranges.size() - 1;
    int index = -1;
    while(left<=right){
        int mid = (left+right)/2;
        if(query>=ranges[mid][0] && query<=ranges[mid][1]){
            index = mid;
            right = mid-1;
        }
        else if(query<ranges[mid][0]){
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    return index;
}
int upperBound(vector<vector<double>> ranges, double query){
    int left = 0;
    int right = ranges.size() - 1;
    int index = -1;
    while(left<=right){
        int mid = (left+right)/2;
        if(query>=ranges[mid][0] && query<=ranges[mid][1]){
            index = mid;
            left = mid+1;
        }
        else if(query<ranges[mid][0]){
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    return index;
}
int main(){
    vector<vector<double>> ranges;
    ranges.push_back({-3.0, 5.2});
    ranges.push_back({6.0, 8.2});
    ranges.push_back({2.2, 5.5});
    ranges.push_back({4.6, 10.1});
    ranges.push_back({4.8, 5.4});
    sort(ranges.begin(), ranges.end());
    double query = 7.1;
    int lowIndex = lowerBound(ranges,query);
    int highIndex = upperBound(ranges, query);
    if(lowIndex == -1 || highIndex == -1){
        cout<<"query out of range"<<" ";
    }
    else{
        for(int i=lowIndex; i<=highIndex;i++){
            cout<<"["<<ranges[i][0]<<" "<<ranges[i][1]<<"] ";
        }
    }
}