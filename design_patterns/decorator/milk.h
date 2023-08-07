#ifndef _MILK_H
#define _MILK_H
#include<string>
#include"beverage.h"
class Milk : public Beverage{
public:
    std::string des ="milk";
    float price = 8;
    std::string getDescription(){return des;}
    float getPrice(){return price;}
};
#endif