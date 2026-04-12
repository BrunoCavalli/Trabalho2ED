#include <iostream>
#include "OrderBook.hpp"
#include "Order.hpp"
#include "Transaction.hpp"

using namespace std;

int main() {
    OrderBook book;

    cout << "===== Estado inicial =====" << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();
    cout << endl;

    cout << "===== Insercao de compra =====" << endl;
    cout << "submit(Order(1, 'B', 10.0, 1)) -> ";
    cout << book.submit(Order(1, 'B', 10.0f, 1)) << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();
    cout << endl;

    cout << "===== Insercao de venda sem execucao =====" << endl;
    cout << "submit(Order(2, 'S', 12.0, 2)) -> ";
    cout << book.submit(Order(2, 'S', 12.0f, 2)) << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();
    cout << endl;

    cout << "===== Insercao de compra e execucao  =====" << endl;
    cout << "submit(Order(3, 'B', 15.0, 3)) -> ";
    cout << book.submit(Order(3, 'B', 15.0f, 3)) << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();
    cout << endl;

    cout << "===== Cancelamento =====" << endl;
    cout << "cancel(1) -> ";
    cout << book.cancel(1) << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();
    cout << endl;

    cout << "cancel(999) -> ";
    cout << book.cancel(999) << endl;
    cout << endl;

    cout << "===== getBuyOrders =====" << endl;
    int nBuy = 0;
    Order* buyOrders = book.getBuyOrders(&nBuy);
    cout << "nBuy = " << nBuy << endl;
    if (buyOrders == nullptr) {
        cout << "(empty)" << endl;
    } else {
        for (int i = 0; i < nBuy; i++) {
            cout << "["
                 << buyOrders[i].getId() << " | "
                 << buyOrders[i].getPrice() << " | "
                 << buyOrders[i].getTimestamp() << "]" << endl;
        }
        delete[] buyOrders;
    }
    cout << endl;

    cout << "===== getSellOrders =====" << endl;
    int nSell = 0;
    Order* sellOrders = book.getSellOrders(&nSell);
    cout << "nSell = " << nSell << endl;
    if (sellOrders == nullptr) {
        cout << "(empty)" << endl;
    } else {
        for (int i = 0; i < nSell; i++) {
            cout << "["
                 << sellOrders[i].getId() << " | "
                 << sellOrders[i].getPrice() << " | "
                 << sellOrders[i].getTimestamp() << "]" << endl;
        }
        delete[] sellOrders;
    }
    cout << endl;

    cout << "===== getTransactions =====" << endl;
    int nTransactions = 0;
    Transaction* transactions = book.getTransactions(&nTransactions);
    cout << "nTransactions = " << nTransactions << endl;
    if (transactions == nullptr) {
        cout << "(empty)" << endl;
    } else {
        for (int i = 0; i < nTransactions; i++) {
            cout << "["
                 << transactions[i].getBuyOrderId() << ", "
                 << transactions[i].getSellOrderId() << ", "
                 << transactions[i].getExecutionPrice() << "]" << endl;
        }
        delete[] transactions;
    }
    cout << endl;

    cout << "===== Estado final =====" << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    return 0;
}