#include <vector>
#include <iostream>
#include<set>
using namespace std;

class ConferenceRoom{
    public:
        set<pair<int,int>> bookedRooms;
        ConferenceRoom(){};
        bool book(int start, int end){
           auto it = bookedRooms.lower_bound({start, INT_MIN});
           if(it==bookedRooms.end()){
                bookedRooms.insert({start, end});
                return true;
           }
           if(end<=it->first && ((it!=bookedRooms.begin() && start>=prev(it)->second) || it==bookedRooms.begin())){
                bookedRooms.insert({start,end});
                return true;
           }
           return false;
        }
};
int main(){
    ConferenceRoom conferenceRoom;
    cout<<conferenceRoom.book(10,20)<<" ";
    cout<<conferenceRoom.book(20,30)<<" ";
    cout<<conferenceRoom.book(5,15)<<" ";
    cout<<conferenceRoom.book(15,25)<<" ";
    cout<<conferenceRoom.book(25,35)<<" ";
    cout<<conferenceRoom.book(1,5)<<" ";
    cout<<conferenceRoom.book(30,40)<<" ";
}