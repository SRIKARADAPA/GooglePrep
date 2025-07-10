
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_set>
using namespace std;

pair<string, string> splitString(string message){
    size_t position = message.find(" ");
    string timestamp = message.substr(0, position);
    string actualMessage = message.substr(position+1, message.size() - position - 1);
    return {timestamp, actualMessage}; 
}
vector<string> filterRecentMessages(vector<string> messages){
    unordered_map<string,int> messageTimes;
    vector<string> filteredMessages;
    for(int i=0;i<messages.size();i++){
        string message = messages[i];
        pair<string,string> processedMessage =  splitString(message);
        int timestamp = stoi(processedMessage.first);
        string actualMessage = processedMessage.second;
        if(messageTimes.count(actualMessage)!=0 && timestamp-messageTimes[actualMessage]<=10){
            continue;
        }
        messageTimes[actualMessage] = timestamp;
        filteredMessages.push_back(message);
    }
    return filteredMessages;
}

vector<string> removeDuplicates(vector<string> messages){
    unordered_map<string,pair<int,int>> messageTimes;
    vector<string> filteredMessages;
    unordered_set<int> untrustedMessageIndices;
    for(int i=0;i<messages.size();i++){
        string message = messages[i];
        pair<string,string> processedMessage =  splitString(message);
        int timestamp = stoi(processedMessage.first);
        string actualMessage = processedMessage.second;
        if(messageTimes.count(actualMessage)!=0 && timestamp-messageTimes[actualMessage].first<=10){
            untrustedMessageIndices.insert(i);
            untrustedMessageIndices.insert(messageTimes[actualMessage].second);
        }
        messageTimes[actualMessage] = {timestamp, i};
    }
    for(int i=0;i<messages.size();i++){
        if(untrustedMessageIndices.find(i)==untrustedMessageIndices.end()){
            filteredMessages.push_back(messages[i]);
        }
    }
    return filteredMessages;
}

int main(){
    vector<string> messages;
    messages.push_back("10 solar panel activated");
    messages.push_back("11 low battery warning");
    messages.push_back("12 tier one: low air pressure");
    messages.push_back("13 solar panel activated");
    messages.push_back("14 low battery warning");
    messages.push_back("21 solar panel activated");
    messages.push_back("35 solar panel activated");
    vector<string> filterRecent = filterRecentMessages(messages);
    for(int i=0;i<filterRecent.size();i++){
        cout<<filterRecent[i]<<" ";
    }
    cout<<"\n";
    vector<string> removeDuplicateMessages = removeDuplicates(messages);
     for(int i=0;i<removeDuplicateMessages.size();i++){
        cout<<removeDuplicateMessages[i]<<" ";
    }
    return 0;
}