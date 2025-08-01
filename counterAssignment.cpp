#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector<int> times = {3,2,5};
    int k = 4;
    int n = times.size();
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(int i=0;i<n;i++){
        pq.push({0,i});
    }
    int ans = 0;
    for(int i=0;i<k;i++){
        int time = pq.top().first;
        int index = pq.top().second;
        pq.pop();
        pq.push({time+times[index], time});
    }
    cout<<pq.top().first + times[pq.top().second]<<" ";
}