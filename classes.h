#ifndef classes_H
#define classes_H
#include <string>
using namespace std;

class Payment // Grandfather class
{
private:
    int amount;

public:
    Payment(const int &amount);
    void payment_details();
};


class CashPayment : public Payment // Multilevel Inheritance with payment class(Father class)
{
private:
    string pay_type;

public:
    // Payment type for the current transaction type
    CashPayment(const int &amount, const string &pay_type = "Cash");

    string get_pay_type();

    void payment_details();
};


#endif