#include "OrderBook.hpp"

OrderBook::OrderBook() {
    buy = nullptr;
    sell = nullptr;
    transactions = nullptr;
}

OrderBook::~OrderBook() {
    //libera Buy Orders
    OrderNode* current = buy;
    while(current != nullptr) {
        OrderNode* next = current->next;
        delete current;
        current = next;
    }

    //liberar Sell Orders
    current = sell;
    while(current != nullptr){
        OrderNode* next = current->next;
        delete current;
        current = next;
    }

    //Liberar a lista de transações
    TransactionNode* current2 = transactions;
    while(current2 != nullptr) {
        TransactionNode* next = current2->next;
        delete current2;
        current2 = next;
    }
}