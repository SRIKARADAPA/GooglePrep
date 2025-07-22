#include <vector>
#include <iostream>
using namespace std;
void printTopK(vector<pair<int,string>> &pathSizes, int k){
    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> topKpaths;
    for(int i=0;i<pathSizes.size();i++){
        if(i<k){
            topKpaths.emplace(pathSizes[i]);
            continue;
        }
        if(pathSizes[i].first>topKpaths.top().first){
            topKpaths.pop();
            topKpaths.emplace(pathSizes[i]);
        }
    }
    vector<string> topPaths;
    while(!topKpaths.empty()){
        topPaths.push_back(topKpaths.top().second);
        topKpaths.pop();
    }
    reverse(topPaths.begin(), topPaths.end());
    for(int i=0;i<topPaths.size();i++){
        cout<<topPaths[i]<<" ";
    }
}
int main(){
    vector<pair<int,string>> pathSizes;
    pathSizes.push_back({12, "abc"});
    pathSizes.push_back({1, "gah"});
    pathSizes.push_back({15, "sasa"});
    pathSizes.push_back({125, "adadas"});
    pathSizes.push_back({2, "ss"});
    pathSizes.push_back({21, "jajsa"});
    pathSizes.push_back({23, "bsa"});
    pathSizes.push_back({13, "ana"});
    pathSizes.push_back({90, "ansna"});
    pathSizes.push_back({65, "uquwq"});
    pathSizes.push_back({11, "addb"});
    pathSizes.push_back({12, "sbhdq"});
    pathSizes.push_back({13, "abbdqq"});
    pathSizes.push_back({100, "nanns"});
    pathSizes.push_back({4, "asnasnad"});
    pathSizes.push_back({9, "dbaba"});
    pathSizes.push_back({32, "nbwbqb"});
    pathSizes.push_back({65, "babdad"});
    pathSizes.push_back({1, "nhrre"});
    pathSizes.push_back({10, "dfehw"});
    printTopK(pathSizes, 10);
}