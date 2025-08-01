#include <vector>
#include <iostream>
using namespace std;
unordered_map<string,string> ans;
bool updateIfValid(unordered_map<char,char> &wordEncodingMap, unordered_map<char,char> &encodingWordMap, string &s1, string &s2){
    if(s1.size()!=s2.size()){
        return false;
    }
    for(int i=0;i<s1.size();i++){
        if(wordEncodingMap.count(s2[i])>0 && wordEncodingMap[s2[i]]!=s1[i]){
            return false;
        }
        if(encodingWordMap.count(s1[i])>0 && encodingWordMap[s1[i]]!=s2[i]){
            return false;
        }
    }
    for(int i=0;i<s1.size();i++){
        if(wordEncodingMap.count(s2[i])>0 && wordEncodingMap[s2[i]]!=s1[i]){
            return false;
        }
        if(encodingWordMap.count(s1[i])>0 && encodingWordMap[s1[i]]!=s2[i]){
            return false;
        }
        wordEncodingMap[s2[i]] = s1[i];
        encodingWordMap[s1[i]] = s2[i];
    }
    return true;
}

void dfs(vector<string> &words, vector<string> &encodings, int wordIndex, int mask, unordered_map<string,string> &wordMap, unordered_map<char,char> &wordEncodingMap,
unordered_map<char,char> &encodingWordMap){
    if(ans.size()>0){
        return;
    }
    if(wordIndex == words.size()){
        ans = wordMap;
        return;
    }
    for(int i=0;i<encodings.size();i++){
        unordered_map<string,string> tempWordMap = wordMap;
        unordered_map<char,char> tempWordEncodingMap = wordEncodingMap;
        unordered_map<char,char> tempEncodingWordMap = encodingWordMap;
        if(!(mask & (1<<i)) && updateIfValid(wordEncodingMap,encodingWordMap,encodings[i], words[wordIndex])){
            wordMap[encodings[i]] = words[wordIndex];
            dfs(words, encodings, wordIndex+1, mask | (1<<i), wordMap, wordEncodingMap, encodingWordMap);
            wordMap = tempWordMap;
            wordEncodingMap = tempWordEncodingMap;
            encodingWordMap = tempEncodingWordMap;
        }
    }
    return;
}
int main(){
    vector<string> words = {"and", "not", "but", "jane", "jordan", "bob"};
    vector<string> encodings = {"qxuw", "xuo", "qeioxu", "tyr", "uer", "tet"};
    int n = words.size();
    unordered_map<string,string> wordMap;
    unordered_map<char,char> wordEncodingMap;
    unordered_map<char,char> encodingWordMap;
    dfs(words, encodings, 0, 0, wordMap, wordEncodingMap, encodingWordMap);
    for(int i=0;i<n;i++){
        cout<<ans[encodings[i]]<<" ";
    }
}