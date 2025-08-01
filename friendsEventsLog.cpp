#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
vector<vector<string>> processLogs(vector<string> eventLogs){
    vector<vector<string>> processedLogs;
    for(int i=0;i<eventLogs.size();i++){
        string token;
        vector<string> tokens;
        stringstream ss(eventLogs[i]);
        while(getline(ss, token, ' ')){
            tokens.push_back(token);
        }
        processedLogs.push_back({tokens[1], tokens[3], tokens[0]});
    }
    return processedLogs;
}
string findParent(string node, unordered_map<string,string> &parentMap){
    if(parentMap[node]!=node){
        parentMap[node] = findParent(parentMap[node], parentMap);
    }
    return parentMap[node];
}
string unionGroups(unordered_map<string,string> &parentMap,  unordered_map<string,int> &groupSizes, vector<vector<string>> &processedLogs, int numFriends){
    string ans = "Not everyone is reachable";
    for(int i=0;i<processedLogs.size();i++){
        string friend1 = processedLogs[i][0];
        string friend2 = processedLogs[i][1];
        string timestamp = processedLogs[i][2];
        string parent1 = findParent(friend1, parentMap);
        string parent2 = findParent(friend2, parentMap);
        if(groupSizes[parent1]>=groupSizes[parent2]){
            parentMap[parent2] = parent1;
            groupSizes[parent1]+=(groupSizes[parent2]);
            if(groupSizes[parent1]==numFriends){
                ans = timestamp;
                break;
            }
        }
        else{
            parentMap[parent1] = parent2;
            groupSizes[parent2]+=(groupSizes[parent1]);
            if(groupSizes[parent2]==numFriends){
                ans = timestamp;
                break;
            }
        }
    }
    return ans;
}
int main(){
    vector<string> friends = {"Alice", "Bob", "Charlie", "Dan", "Erin", "ahah"};
    vector<string> eventLogs = {"1648305616 Alice and Bob became friends", "1648305678 Charlie and Dan became friends", "1648306171 Bob and Charlie became friends", 
        "1648306237 Alice and Erin became friends"};
    vector<vector<string>> processedLogs = processLogs(eventLogs);
    unordered_map<string,string> parentMap;
    unordered_map<string,int> groupSizes;
    for(int i=0;i<friends.size();i++){
        parentMap[friends[i]] = friends[i];
        groupSizes[friends[i]] = 1;
    }
    cout<<unionGroups(parentMap, groupSizes, processedLogs, friends.size())<<" ";
}   