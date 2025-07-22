#include <vector>
#include <iostream>
using namespace std;
class Iterator{
    public:
        int index = 0;
        int size;
        vector<int> arr;
        Iterator(vector<int> v){
            arr = v;
            size = v.size();
            while(index<size && arr[index] == 0){
                index+=2;
            }
        }
        int next(){
            arr[index]--;
            int ans = arr[index+1];
            while(index<size && arr[index] == 0){
                index+=2;
            }
            return ans;
        }
        bool hasNext(){
            return index<size;
        }
};
int main(){
    vector<int> v = {1,2,0,1,3,4};
    Iterator it(v);
    while(it.hasNext()){
        cout<<it.next()<<" ";
    }
}