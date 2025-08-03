#include <vector>
#include <iostream>
using namespace std;

class MusicPlayer{
    public:
        vector<string> availableSongs;
        queue<string> unavailableSongs;
        int k;
        MusicPlayer(vector<string> inputSongs, int K){
            availableSongs = inputSongs;
            k=K;
        }
        string findSong(){
            int numSongs = availableSongs.size();
            int index = rand()%numSongs;
            string song = availableSongs[index];
            swap(availableSongs[index], availableSongs[availableSongs.size()-1]);
            unavailableSongs.push(song);
            availableSongs.erase(availableSongs.begin() + availableSongs.size() - 1);
            if(unavailableSongs.size()>k){
                string frontSong = unavailableSongs.front();
                unavailableSongs.pop();
                availableSongs.push_back(frontSong);
            }
            return song;
        }
};

class MusicPlayer2{
        public:
            unordered_map<string,int> availableSongsMap;
            vector<pair<string,int>> availableSongs;
            priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> unavailableSongs;
            int iterationCount = 0;
            MusicPlayer2(vector<pair<string,int>> inputSongs){
                availableSongs = inputSongs;
                for(int i=0;i<inputSongs.size();i++){
                    availableSongsMap[inputSongs[i].first] = inputSongs[i].second;
                }
            }
            string findSong(){
                while(!unavailableSongs.empty() && unavailableSongs.top().first<=iterationCount){
                    availableSongs.push_back({unavailableSongs.top().second, availableSongsMap[unavailableSongs.top().second]});
                    unavailableSongs.pop();
                }
                iterationCount++;
                if(availableSongs.size()==0){
                    return "No songs available at the moment";
                }
                int numSongs = availableSongs.size();
                int index = rand()%numSongs;
                string song = availableSongs[index].first;
                int kCount = availableSongs[index].second;
                swap(availableSongs[index], availableSongs[availableSongs.size()-1]);
                unavailableSongs.push({iterationCount+kCount,song});
                availableSongs.erase(availableSongs.begin() + availableSongs.size() - 1);
                return song;
            }
};
int main(){
    vector<pair<string,int>> songs = {{"A",10}, {"B",30}, {"C",20}, {"D",4}, {"E",2}};
    int k = 2;
    MusicPlayer2 musicPlayer(songs);
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
    cout<<musicPlayer.findSong()<<" ";
}