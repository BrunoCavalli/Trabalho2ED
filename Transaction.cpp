#include "Transaction.hpp"
#include "OrderBook.hpp"

Transaction::Transaction(int buy_order_id, int sell_order_id, float execution_price){
    this->buy_order_id = buy_order_id;
    this->sell_order_id = sell_order_id;
    this->execution_price = execution_price;
}

Transaction::~Transaction(){

}