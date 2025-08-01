#include <vector> 
#include <iostream>
#include <sstream>
using namespace std;

vector<string> split(string s){
    stringstream ss(s);
    string token;
    vector<string> tokens;
    while(getline(ss, token, ' ')){
        tokens.push_back(token);
    }
    return tokens;
}
vector<vector<string>> processLogs(vector<string> &logs){
    int n = logs.size();
    vector<vector<string>> processedLogs;
    for(int i=0;i<n;i++){
        vector<string> log = split(logs[i]);
        processedLogs.push_back(log);
    }
    return processedLogs;
}
int main(){
    vector<string> logs = { "Start 1 req1",
                            "Finish 2 req1",
                            "Start 3 req2",
                            "Start 4 req3",
                            "Start 5 req4",
                            "Finish 6 req4",
                            "Finish 7 req3",
                            "Finish 8 req2"};
    vector<vector<string>> splitLogs = processLogs(logs);
    unordered_map<string,string> mp;
    int n = splitLogs.size();
    for(int i=0;i<n;i++){
        if(splitLogs[i][0] == "Start"){
            mp[splitLogs[i][2]] = splitLogs[i][1];
        }
        else{
            cout<<splitLogs[i][2]+ " started at " + mp[splitLogs[i][2]] + " and ended at " + splitLogs[i][1] + "\n";
        }
    }
}