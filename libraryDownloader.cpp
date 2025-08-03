#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

void buildReverseDependencies(unordered_map<string,int> &inDegree, unordered_map<string, vector<string>> &dependencies, unordered_map<string, vector<string>> &reverseDependencies){
    for(auto it = dependencies.begin(); it!=dependencies.end(); it++){
        vector<string> neighbors = it->second;
        for(int i=0;i<neighbors.size();i++){
            string neighbor = neighbors[i];
            reverseDependencies[neighbor].push_back(it->first);
            inDegree[it->first]++;
        }
    }
    return;
}
int topSort(unordered_map<string,int> &inDegree, unordered_map<string, vector<string>> &reverseDependencies, unordered_map<string, int> &downloadTimes, int x){
    int currTime = 0;
    priority_queue<pair<string,int>, vector<pair<string,int>>, greater<pair<string,int>>> availableDependencies;
    unordered_set<string> downloaded;
    for(auto it = inDegree.begin(); it!=inDegree.end();it++){
        if(it->second==0){
            downloaded.insert(it->first);
            availableDependencies.push({it->first, downloadTimes[it->first]});
        }
    }
    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> topXdependencies;
    while(!availableDependencies.empty() || !topXdependencies.empty()){
        while(!availableDependencies.empty() && topXdependencies.size()<x){
            topXdependencies.push({currTime + availableDependencies.top().second, availableDependencies.top().first});
            availableDependencies.pop();
        }
        if(!topXdependencies.empty()){
            currTime = topXdependencies.top().first;
            while(!topXdependencies.empty() && topXdependencies.top().first == currTime){
                pair<int,string> topDependency = topXdependencies.top();
                string dependencyString = topDependency.second;
                cout<<dependencyString<<" ";
                topXdependencies.pop();
                vector<string> neighbors = reverseDependencies[dependencyString];
                for(int i=0;i<neighbors.size();i++){
                    if(downloaded.count(neighbors[i])==0){
                        inDegree[neighbors[i]]--;
                        if(inDegree[neighbors[i]]==0){
                            downloaded.insert(neighbors[i]);
                            availableDependencies.push({neighbors[i],downloadTimes[neighbors[i]]});
                        }
                    }
                }
            }
        }
    }
    return currTime;
}
int main(){
    unordered_map<string, vector<string>> dependencies;
    dependencies["tesla-client"] = {"tesla-common", "tesla-http", "tesla-ui"};
    dependencies["tesla-common"] = {"junit"};
    dependencies["tesla-http"] = {"http-client", "tesla-logs"};
    dependencies["tesla-ui"] = {"tesla-grid"};
    dependencies["http-client"] = {"http-core"};
    dependencies["tesla-grid"] = {"tesla-rows", "tesla-cols"};
    unordered_map<string, int> downloadTimes;
    downloadTimes["tesla-client"] = 7;
    downloadTimes["tesla-common"] = 3;
    downloadTimes["tesla-http"] = 12;
    downloadTimes["tesla-ui"] = 10;
    downloadTimes["junit"] = 9;
    downloadTimes["http-client"] = 11;
    downloadTimes["tesla-logs"] = 13;
    downloadTimes["tesla-grid"] = 8;
    downloadTimes["http-core"] = 5;
    downloadTimes["tesla-cols"] = 9;
    downloadTimes["tesla-rows"] = 6;
    unordered_map<string, vector<string>> reverseDependencies;
    unordered_map<string,int> inDegree;
    int x=3;
    for(auto it = downloadTimes.begin();it!=downloadTimes.end();it++){
        inDegree[it->first] = 0;
    }
    buildReverseDependencies(inDegree, dependencies, reverseDependencies);
    cout<<topSort(inDegree, reverseDependencies, downloadTimes, x)<<" ";
}