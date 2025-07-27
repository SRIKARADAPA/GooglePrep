#include <iostream>
#include <vector>
using namespace std;

int find(vector<int> &parent, int node){
    if(parent[node]!=node){
        parent[node] = find(parent, parent[node]);
    }
    return parent[node];
}
void unionPairs(vector<int> &parent, int node1, int node2, vector<int> &rank){
    int parent1 = find(parent, node1);
    int parent2 = find(parent, node2);
    if(parent1==parent2){
        return;
    }
    if(rank[parent1]>rank[parent2]){
        parent[parent2] = parent1;
    }
    else if(rank[parent1]==rank[parent2]){
        rank[parent1]++;
        parent[parent2] = parent1;
    }
    else{
        rank[parent1] = parent2;
    }
    return;
}
int unionFind(vector<vector<int>> &pairs, int n){
    vector<int> parent(n);
    vector<int> rank(n,1);
    for(int i=0;i<n;i++){
        parent[i] = i;
    }
    for(int i=0;i<pairs.size();i++){
        unionPairs(parent, pairs[i][0], pairs[i][1], rank);
    }
    vector<int> parentCounts(n,0);
    for(int i=0;i<n;i++){
        parentCounts[find(parent, parent[i])]++;
    }
    int ans = 0;
    int sum=n;
    for(int i=0;i<n;i++){
        ans+=(parentCounts[i] * (sum-parentCounts[i]));
        sum-=parentCounts[i];
    }
    return ans;
}
int main(){
    int n=4;
    vector<vector<int>> pairs = {{0,1}, {1,2}, {2,0}};
    cout<<unionFind(pairs,n);
}