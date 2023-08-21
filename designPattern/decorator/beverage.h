#ifndef _BEVERAGE_H
#define _BEVERAGE_H
#include<string>
class Beverage{
public:
    std::string des ="";
    float price = 0;
    virtual std::string getDescription()=0;
    virtual float getPrice()=0;
};
#endif