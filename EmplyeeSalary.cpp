#include <vector>
#include <iostream>
using namespace std;

class Employee{
    public: 
        string id;
        int employeeSalary;
        vector<Employee> subordinates;
        Employee(string ID, int salary){
            id = ID;
            employeeSalary = salary;
        }
        void addSubordinate(Employee subordinate){
            subordinates.push_back(subordinate);
        }
};
vector<Employee> findUnderpaidManagers(Employee emp1){
    vector<Employee> underpaidManagers;
    queue<Employee> managers;
    managers.push(emp1);
    while(!managers.empty()){
        Employee manager = managers.front();
        managers.pop();
        if(manager.subordinates.size()==0){
            continue;
        }
        int numSubordinates = manager.subordinates.size();
        int totalSubordinatesSalary = 0;
        for(int i=0;i<numSubordinates;i++){
            managers.push(manager.subordinates[i]);
            totalSubordinatesSalary+=(manager.subordinates[i].employeeSalary);
        }
        if(((double)(totalSubordinatesSalary))/((double)numSubordinates)>manager.employeeSalary){
            underpaidManagers.push_back(manager);
        }
    }
    return underpaidManagers;
}
int main(){
    Employee emp1("Employee1", 75000);
    Employee emp2("Employee1", 80000);
    Employee emp3("Employee1", 100000);
    Employee emp4("Employee1", 90000);
    emp1.addSubordinate(emp2);
    emp1.addSubordinate(emp4);
    emp2.addSubordinate(emp3);
    vector<Employee> underPaidManagers = findUnderpaidManagers(emp1);
    for(int i=0;i<underPaidManagers.size();i++){
        cout<<underPaidManagers[i].id<<" ";
    }
}