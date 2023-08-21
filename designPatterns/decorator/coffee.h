#ifndef _COFFEE_H
#define _COFFEE_H
#include<string>
#include"beverage.h"
class Coffee : public Beverage{
public:
    std::string des ="coffee";
    float price = 10;
    std::string getDescription(){return des;}
    float getPrice(){return price;}
};
#endif