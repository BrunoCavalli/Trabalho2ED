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

void OrderBook::insertSellOrder(Order order){
    OrderNode* newNode = new OrderNode;
    newNode->order = order;
    newNode->next = sell;
    sell = newNode;
}

void OrderBook::RemoveSellOrder(Order order) {
    if (sell == nullptr) return;

    if(sell->order.getId() == order.getId()) {
        OrderNode* temp = sell;
        sell = sell->next;
        delete temp;
        return;
    }

    OrderNode* current = sell;
    while (current->next != nullptr && current->next->order.getId() != order.getId()){
        current = current->next;
    }

    if(current->next != nullptr){
        OrderNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

void OrderBook::RemoveBuyOrder(Order order){
    if(buy == nullptr) return;

    if(buy->order.getId() == order.getId()){
        OrderNode* temp = buy;
        buy = buy->next;
        delete temp;
        return;
    }

    OrderNode* current = buy;
    while (current->next != nullptr && current->next->order.getId() != order.getId()){
        current = current->next;
    }

    if(current->next != nullptr){
        OrderNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }    

}

void OrderBook::insertTransaction(Transaction transaction){
    TransactionNode* newNode = new TransactionNode;
    newNode->transaction = transaction;
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
            }
            current = current->next;
        }
        if (best != nullptr) { // achou contraparte -> executa a transação
            Transaction t(order.getId(),best->order.getId(), best->order.getPrice()); // order é a compra e best->order é venda
            insertTransaction(t);
            RemoveSellOrder(best->order);
            return true;

        } else { // não achou acontraparte -> inseri na lista de pedidos de comprar (buy)
            insertBuyOrder(order);
            return false;
        }

    }
    
    if(order.getType() == 'S'){
        OrderNode* best = nullptr;
        OrderNode* current = buy;

        while(current != nullptr) {
            if(current->order.getPrice() >= order.getPrice()){
                if(best == nullptr) {
                    best = current;
                } else if(current->order.getPrice() > best->order.getPrice()){
                    best = current;
                } else if (current->order.getPrice() == best->order.getPrice() && current->order.getTimestamp() < best->order.getTimestamp()){
                    best = current;
                }
            }
            current = current->next;
        }
        if (best != nullptr) { // achou contraparte -> executa a transação
            Transaction t(best->order.getId(),order.getId(), best->order.getPrice()); // best->order é compra e order é a venda 
            insertTransaction(t);
            RemoveBuyOrder(best->order);
            return true;

        } else { // não achou acontraparte -> inseri na lista de pedidos de venda (sell)
            insertSellOrder(order);
            return false;
        }

    }
    return false;
}

// Retorna um array com as orders de compra que temos. Como não sabemos o tamanho das orders, teremos que varrer ela antes
Order* OrderBook::getBuyOrders(int* n){
    int count = 0;
    OrderNode* current = buy;

    while(current != nullptr){
        count++;
        current = current->next;
    }

    *n = count;
    
    if(count==0){
        return nullptr;
    }

    Order* orders = new Order[count];

    current = buy;
    int i = 0;
    while(current!=nullptr){
        orders[i] = current->order;
        i++;
        current = current->next;
    }

    return orders;
}

// Repete a mesma lógica para as ordens de venda
Order* OrderBook::getSellOrders(int* n){
    int count = 0;
    OrderNode* current = sell;

    while(current != nullptr){
        count++;
        current = current->next;
    }

    *n = count;
    
    if(count==0){
        return nullptr;
    }

    Order* orders = new Order[count];

    current = sell;
    int i = 0;
    while(current!=nullptr){
        orders[i] = current->order;
        i++;
        current = current->next;
    }

    return orders;
}

// Repete a mesma lógica para transactions, mas mudando o objeto pra transactions
Transaction* OrderBook::getTransactions(int* n){
    int count = 0;
    TransactionNode* current = transactions;

    while(current != nullptr){
        count++;
        current = current->next;
    }

    *n = count;
    
    if(count==0){
        return nullptr;
    }

    Transaction* result = new Transaction[count];

    current = transactions;
    int i = 0;
    while(current!=nullptr){
        result[i] = current->transaction;
        i++;
        current = current->next;
    }

    return result;
}

// Por fim, montando funções que varrem as orders e printam
void OrderBook::printBuyOrders(){
    std::cout<<"Buy orders:"<< std::endl;
    if(buy==nullptr){
        std::cout<<"(empty)"<<std::endl;
        return;
    }
    OrderNode* current = buy;
    while(current!=nullptr){
        std::cout<<"["<<current->order.getId()<<" | "<<current->order.getPrice()<<" | "<<current->order.getTimestamp()<<"]"<<std::endl;
        current = current->next;
    }
}

void OrderBook::printSellOrders(){
    std::cout<<"Sell orders:"<< std::endl;
    if(sell==nullptr){
        std::cout<<"(empty)"<<std::endl;
        return;
    }
    OrderNode* current = sell;
    while(current!=nullptr){
        std::cout<<"["<<current->order.getId()<<" | "<<current->order.getPrice()<<" | "<<current->order.getTimestamp()<<"]"<<std::endl;
        current = current->next;
    }
}

void OrderBook::printTransactions(){
    std::cout<<"Transactions:"<<std::endl;
    if(transactions==nullptr){
        std::cout<<"(empty)"<<std::endl;
        return;
    }
    TransactionNode* current = transactions;
    while(current!=nullptr){
        std::cout<<"["<<current->transaction.getBuyOrderId()<<", "<<current->transaction.getSellOrderId()<<", "<<current->transaction.getExecutionPrice()<<"]"<<std::endl;
        current = current->next;
    }
}