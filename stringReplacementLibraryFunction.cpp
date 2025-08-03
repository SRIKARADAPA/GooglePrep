#include <vector>
#include <iostream>
using namespace std;

string processString(string input, unordered_map<string, string> &replacementsMap){
    int n = input.size();
    string processedString = "";
    int i=0;
    while(i<n){
        if(input[i]!='%'){
            processedString+=(input[i]);
            i++;
            continue;
        }
        string temp = "";
        i++;
        while(i<n && input[i]!='%'){
            temp+=(input[i]);
            i++;
        }
        if(replacementsMap.count(temp)>0){
            processedString+=(replacementsMap[temp]);
        }
        else{
            processedString+="%"+temp+"%";
        }
        i++;
    }
    return processedString;
}
int main(){
    unordered_map<string, string> replacementsMap;
    replacementsMap["A"] = "%B%";
    replacementsMap["B"] = "%Z%";
    replacementsMap["Z"] = "success";
    replacementsMap["NAME"] = "John";
    string inputString = "Hello, %NAME%! Meet %KNOWN%. %B%";
    for(auto it = replacementsMap.begin();it!=replacementsMap.end();it++){
        string prevString = "";
        string currString = it->second;
        while(currString!=prevString){
            prevString = currString;
            currString = processString(currString, replacementsMap);
        }
        it->second = currString;
    }
    cout<<processString(inputString, replacementsMap);
}