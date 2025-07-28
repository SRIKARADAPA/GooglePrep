#include <iostream>
#include <vector>
#include <set>
using namespace std;

void f(vector<int> &arr, int val, set<double> &ans, int mask, int n){
    if(mask == pow(2,n)-1){
        if(val>0){
            ans.insert(val);
        }
        return;
    }
    for(int i=0;i<n;i++){
        if(!(mask & (1<<i))){
            f(arr, val+arr[i], ans, mask | (1<<i), n);
            f(arr, val*arr[i], ans, mask | (1<<i), n);
            f(arr, val-arr[i], ans, mask | (1<<i), n);
            if(arr[i]!=0){
                f(arr, val/arr[i], ans, mask | (1<<i), n);
            }
            if(val!=0){
                f(arr, arr[i]/val, ans, mask | (1<<i), n);
            }
        }
    }
    return;
}
int main(){
    vector<int> arr = {2,4,5};
    int n = arr.size();
    set<double> ans;
    f(arr, 0, ans, 0, n);
    int val = 1;
    for(int num: ans){
        if(num==val){
            val++;
        }
        else{
            break;
        }
    }
    cout<<val<<" ";
}