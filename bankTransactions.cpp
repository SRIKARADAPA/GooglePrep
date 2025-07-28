#include <iostream>
#include <vector>
using namespace std;

int main(){
    int initialMoney = 1;
    vector<int> transactions = {1,-3,5,-2,1};
    int n = transactions.size();
    int index = 0;
    int ans = 0;
    int money = initialMoney;
    int left = 0;
    int right = 0;
    while(right<n){
        money+=(transactions[right]);
        if(money>=0){
            ans = max(ans, right-left+1);
            right++;
            continue;
        }
        while(left<=right && money<0){
            money-=(transactions[left]);
            left++;
        }
        right++;
    }
    cout<<ans<<" ";
}