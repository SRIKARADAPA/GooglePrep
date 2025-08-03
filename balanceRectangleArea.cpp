#include <vector>
#include <iostream>
using namespace std;

double bestLine(vector<vector<int>> &rectangles, double totalArea, double minX, double maxX){
    double left = minX;
    double right = maxX;
    double minDiff = INT_MAX;
    double ans = -1;
    while(right-left>1e-5){
        double mid = (left+right)/2.0;
        double leftArea = 0;
        for(int i=0;i<rectangles.size();i++){
            if(mid<=rectangles[i][0]){
                continue;
            }
            else{
                leftArea+=((double)(rectangles[i][3]-rectangles[i][1])*(min((double)(rectangles[i][2]),mid)-(double)rectangles[i][0]));
            }
        }
        double areaDiff = totalArea - (2.0*leftArea);
        if(abs(areaDiff)<minDiff){
            ans = mid;
            minDiff = abs(areaDiff);
        }
        if(areaDiff==0){
            return mid;
        }
        else if(areaDiff > 0){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    return ans;
}
int main(){
    vector<vector<int>> rectangles = {{1,1,3,3}, {1,1,4,4}, {4,1,6,3}, {3,1,6,3}};
    double totalArea = 0;
    double maxX = INT_MIN;
    double minX = INT_MAX;
    for(int i=0;i<rectangles.size();i++){
        maxX = max(maxX, (double)rectangles[i][2]);
        minX = min(minX, (double)rectangles[i][0]);
        totalArea+=((rectangles[i][2]-rectangles[i][0])*(rectangles[i][3]-rectangles[i][1]));
    }
    cout<<bestLine(rectangles, totalArea, minX, maxX);
}