#include <vector>
#include <iostream>
using namespace std;

int maxScore = 0;
string mergeStrings(string s1, string s2){
    int size = min(s1.size(), s2.size());
    string mergedString = s1+s2;
    for(int i=size-1;i>0;i--){
        string str2 = s2.substr(0,i);
        string str1 = s1.substr(s1.size()-i);
        if(str1 == str2){
            return s1.substr(0,s1.size()-i) + str1 + s2.substr(i);
        }
    }
    return mergedString;
}
void f(vector<string> &words, int index, vector<int> &scores, string curr, int currScore, int limit, unordered_map<string,int> &mp){
    if(curr.size()>limit){
        return;
    }
    if(mp[curr]>currScore){
        return;
    }
    mp[curr] = currScore;
    maxScore = max(maxScore, currScore);
    for(int i=0;i<words.size();i++){
        if(i>0 && words[i]==words[i-1]){
            continue;
        }
        string mergedString = mergeStrings(curr, words[i]);
        currScore+=scores[i];
        f(words, index, scores, mergedString, currScore, limit, mp);
        currScore-=scores[i];
    }
    return;
}
int main(){
    vector<string> words = {"acknowledge", "edged", "pack"};
    unordered_map<string,int> mp;
    vector<int> scores = {12,3,2};
    int limit = 13;
    f(words, 0, scores, "",0, limit,mp);
    cout<<maxScore<<" ";
}