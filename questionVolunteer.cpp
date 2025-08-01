#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

bool isIntersection(unordered_set<string> s1, unordered_set<string> s2){
    for(string knowSubject : s1){
        if(s2.count(knowSubject)>0){
            return true;
        }
    }
    return false;
}
void buildGraph(unordered_map<string, unordered_set<string>> &volunteersMap, unordered_map<string, unordered_set<string>> &questionsMap, 
    unordered_map<string, vector<string>> &adjacencyList){
       for(auto it = volunteersMap.begin();it!=volunteersMap.end();it++){
            string volunteer = it->first;
            unordered_set<string> knownSubjects = it->second;
            for(auto it2 = questionsMap.begin();it2!= questionsMap.end();it2++){
                string question = it2->first;
                unordered_set<string> subjects = it2->second;
                if(isIntersection(knownSubjects, subjects)){
                    adjacencyList[volunteer].push_back(question);
                }
            }
       }
}
bool dfs(string volunteer, unordered_map<string, vector<string>> &adjacencyList, unordered_map<string,string> &assigned, unordered_set<string> &visited){
    vector<string> possibleQuestions = adjacencyList[volunteer];
    for(int i=0;i<possibleQuestions.size();i++){
        if(visited.count(possibleQuestions[i])==0){
            visited.insert(possibleQuestions[i]);
            if(assigned.count(possibleQuestions[i])==0 || dfs(assigned[possibleQuestions[i]], adjacencyList, assigned, visited)){
                assigned[possibleQuestions[i]] = volunteer;
                return true;
            }
        }
    }
    return false;
}
int main(){
    unordered_map<string, unordered_set<string>> questionsMap;
    unordered_map<string, unordered_set<string>> voluteersMap;
    questionsMap["1"] = {"MAC", "VSCODE"};
    questionsMap["2"] = {"PY", "AI"};
    questionsMap["3"] = {"JAVA", "OS"};
    questionsMap["4"] = {"PY", "NW"};
    voluteersMap["A"] = {"PY", "NW"};
    voluteersMap["B"] = {"AI"};
    voluteersMap["C"] = {"JAVA", "ABC"};
    voluteersMap["D"] = {"JAVA", "NW"};
    unordered_map<string, vector<string>> adjacencyList;
    buildGraph(voluteersMap, questionsMap, adjacencyList);
    unordered_map<string,string> assigned;
    for(auto it=voluteersMap.begin();it!=voluteersMap.end();it++){
        unordered_set<string> visited;
        dfs(it->first, adjacencyList, assigned, visited);
    }
    for(auto it = assigned.begin(); it!=assigned.end();it++){
        cout<<"Question " + it->first + " assigned to volunteer " + it->second + "\n";
    }
}