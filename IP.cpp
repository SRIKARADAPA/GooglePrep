#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
vector<string> streamString(string s){
    vector<string> tokens;
    string token;
    stringstream ss(s);
    while(getline(ss, token, '.')){
        tokens.push_back(token);
    }
    return tokens;
}
int compare(string startIp, string endIp, vector<string> inputIpSplit){
    vector<string> startIpSplit = streamString(startIp);
    vector<string> endIpSplit = streamString(endIp);
    if(inputIpSplit>=startIpSplit && inputIpSplit<=endIpSplit){
        return 0;
    }
    else if(inputIpSplit<startIpSplit){
        return -1;
    }
    else{
        return 1;
    }
}
string binarySearch(vector<vector<string>> cityIps, vector<string> inputIpSplit){
    int left = 0;
    int right = cityIps.size() - 1;
    while(left<=right){
        int mid = (left+right)/2;
        int compareResult = compare(cityIps[mid][1], cityIps[mid][2], inputIpSplit);
        if(compareResult==0){
            return cityIps[mid][0];
        }
        else if(compareResult==1){
            left = mid+1;
        }
        else{
            right = mid-1;
        }
    }
    return "City Not Found";
}
int main(){
    vector<vector<string>> cityIps;
    vector<string> ip1 = {"NYC", "1.0.1.1", "1.0.1.10"};
    vector<string> ip2 = {"SFC", "1.0.1.20", "1.0.1.30"};
    vector<string> ip3 = {"TXC", "2.3.0.1", "4.7.0.254"};
    cityIps.push_back(ip1);
    cityIps.push_back(ip2);
    cityIps.push_back(ip3);
    string inputIp = "1.0.1.25";
    vector<string> inputIpSplit = streamString(inputIp);
    string city = binarySearch(cityIps, inputIpSplit);
    cout<<city<<" ";
    return 0;
}