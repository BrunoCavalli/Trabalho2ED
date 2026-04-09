#include "Transaction.hpp"
#include "Order.hpp"


struct OrderNode {
    Order order;
    OrderNode* next;
};

struct TransactionNode {
    Transaction transaction;
    TransactionNode* next;
};


class OrderBook {

private:

   // Criei listas para cada um dos tipos de operações
    OrderNode* buy;
    OrderNode* sell;
    TransactionNode* transactions;

    
public:

    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();
    void insertBuyOrder(Order order); // inseri no incio da lista buy
    void insertSellOrder(Order order);
    void insertTransaction(Transaction transaction); // inseri no inicio da lista transactions
    void RemoveBuyOrder(Order order);
    void RemoveSellOrder(Order order);

    // Outros métodos auxiliares, se necessário
};