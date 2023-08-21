#ifndef _Calculator_H
#define _Calculator_H
#include<iostream>
class Calculator{
    private:
        float rmb;
    public:
        float price=0;
        // 一旦给出了一种构造函数，就没有默认的构造函数了
        Calculator(){}
        Calculator(float rmb): price(rmb) {}
        float calculatePrice(float);
};
#endif