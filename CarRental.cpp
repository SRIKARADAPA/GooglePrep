#include <vector>
#include <iostream>
using namespace std;
struct RentalRecord{
    int id;
    int pickupTime;
    int returnTime;
    RentalRecord(int id, int p, int r) : id(id), pickupTime(p), returnTime(r) {}
};
class CarRental{
    public:
    pair<int,unordered_map<int,int>> findAssignment(vector<RentalRecord> rentalRecords){
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> assignedCars;
        int carCounter = 1;
        unordered_map<int,int> carAssignment;
        int minCarsNeeded = 1;
        sort(rentalRecords.begin(), rentalRecords.end(), [](RentalRecord record1, RentalRecord record2){
            if(record1.pickupTime == record2.pickupTime){
                return record1.returnTime<record2.returnTime;
            }
            return record1.pickupTime<record2.pickupTime;
        });
        assignedCars.emplace(rentalRecords[0].returnTime, 1);
        carAssignment[rentalRecords[0].id] = 1;
        for(int i=1;i<rentalRecords.size();i++){
            if(assignedCars.top().first<=rentalRecords[i].pickupTime){
                int carNumber = assignedCars.top().second;
                assignedCars.pop();
                assignedCars.emplace(rentalRecords[i].returnTime, carNumber);
                carAssignment[rentalRecords[i].id] = carNumber;
            }
            else{
                carCounter++;
                assignedCars.emplace(rentalRecords[i].returnTime, carCounter);
                carAssignment[rentalRecords[i].id] = carCounter;
            }
        }
        return {carCounter, carAssignment};
    }
};
int main(){
    vector<RentalRecord> rentalRecords;
    rentalRecords.emplace_back(1, 4, 10);
    rentalRecords.emplace_back(2, 2, 3);
    rentalRecords.emplace_back(3, 5, 9);
    rentalRecords.emplace_back(4,1,2);
    rentalRecords.emplace_back(5,8,14);
    rentalRecords.emplace_back(6,11,13);
    CarRental carRental;
    pair<int,unordered_map<int,int>> ans = carRental.findAssignment(rentalRecords);
    cout<<"Minimal cars needed are "<<ans.first<<"\n";
    for(auto it=ans.second.begin(); it!=ans.second.end();it++){
        cout<<"rental Id: "<<it->first<<" "<<"car number "<<it->second<<"\n";
    }
}