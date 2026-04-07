#include "OrderBook.hpp"
#include "Order.hpp"
#include <iostream>

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

void OrderBook::insertBuyOrder(Order order){
    OrderNode* newNode = new OrderNode;
    newNode->order = order;
    newNode->next = buy;
    buy = newNode;
}

void OrderBook::insertTransaction(Transaction transaction){
    TransactionNode* newNode = new TransactionNode;
    newNode->transaciton = transaction;
    newNode->next = transactions;
    transactions = newNode;
}

bool OrderBook::submit(Order order){
    if(order.getType() == 'B'){
        OrderNode* best = nullptr;
        OrderNode* current = sell;

        while(current != nullptr) {
            if(current->order.getPrice() <= order.getPrice()){
                if(best == nullptr) {
                    best = current;
                } else if(current->order.getPrice() < best->order.getPrice()){
                    best = current;
                } else if (current->order.getPrice() == best->order.getPrice() && current->order.getTimestamp() < best->order.getTimestamp()){
                    best = current;
                }
                current = current->next;
            }
        }
        if (best != nullptr) { // achou contraparte -> executa a transação
            Transaction t(order.getId(),best->order.getId(), best->order.getPrice());
            insertTransaction(t);
            // remover da lista buy
            return true;

        } else { // não achou acontraparte -> inseri na lista de pedidos de comprar (buy)
            insertBuyOrder(order);
            return false;
        }

    }    
}