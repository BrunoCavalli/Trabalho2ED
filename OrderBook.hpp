#include "Transaction.hpp"
#include "Order.hpp"


struct OrderNode {
    Order order;
    OrderNode* next;
};

struct TransactionNode {
    Transaction transaciton;
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

    // Outros métodos auxiliares, se necessário
};