class Transaction {

private:
    int buy_order_id;
    int sell_order_id;
    float execution_price;

public:

    Transaction() : buy_order_id(0), sell_order_id(0), execution_price(0.0) {}
    Transaction(int buy_order_id, int sell_order_id, float execution_price);
    ~Transaction();

    int getBuyOrderId();
    int getSellOrderId();
    float getExecutionPrice();
};