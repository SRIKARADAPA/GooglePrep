#include <vector> 
#include <iostream>
#include <sstream>
#include <unordered_set>
using namespace std;

void processFile(string fileName,unordered_map<string, unordered_set<string>> &directoryFilesMap){
    stringstream ss(fileName);
    string token;
    vector<string> tokens;
    while(getline(ss, token, '/')){
        tokens.push_back(token);
    }
    string directory = "";
    string file = "";
    int n = tokens.size();
    for(int i=0;i<n;i++){
        if(i==n-1){
            file = tokens[i];
        }
        else{
            directory+=(tokens[i]);
            if(i<n-2){
                directory+=("/");
            }
        }
    }
    directoryFilesMap[directory].insert(file);
    return;
}
int main(){
    unordered_map<string, unordered_set<string>> directoryFilesMap;
    unordered_map<string,unordered_set<string>> selectedFilesMap;
    vector<string> files = {"/a/b/x.txt","/a/b/p.txt","/a/d/y.txt","/a/d/z.txt"};
    for(int i=0;i<files.size();i++){
        processFile(files[i], directoryFilesMap);
    }
    vector<string> selectedFiles = {"/a/d/y.txt","/a/d/z.txt","/a/b/p.txt"};
    for(int i=0;i<selectedFiles.size();i++){
        processFile(selectedFiles[i], selectedFilesMap);
    }
    vector<string> ans;
    for(auto it = selectedFilesMap.begin();it!=selectedFilesMap.end();it++){
        string directory = it->first;
        if(it->second.size() == directoryFilesMap[directory].size()){
            ans.push_back(directory);
        }
        else{
            for(string file: it->second){
                ans.push_back(directory + "/" + file);
            }
        }
    }
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
}