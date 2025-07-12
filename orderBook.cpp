#include <vector>
#include <iostream>
using namespace std;

class OrderBook{
    public:
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> orders;
        void insertOrder(int price, int timestamp, int sellerId){
            orders.push({price, timestamp, sellerId});
        }
        int getLowestSellerId(){
            vector<int> lowestOrder = orders.top();
            orders.pop();
            return lowestOrder[2];
        }
};
int main(){
    OrderBook orderBook;
    orderBook.insertOrder(20, 10, 1);
    orderBook.insertOrder(10, 20, 2);
    orderBook.insertOrder(30, 5, 3);
    orderBook.insertOrder(10, 10, 4);
    cout<<orderBook.getLowestSellerId()<<" ";
    cout<<orderBook.getLowestSellerId()<<" ";
    cout<<orderBook.getLowestSellerId()<<" ";
}