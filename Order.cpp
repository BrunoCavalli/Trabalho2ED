#include "Order.hpp"
#include <iostream>
#include "OrderBook.hpp"

Order::Order(int id, char type, float price, int timestamp){
    this->id =id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
}

Order::~Order(){

}