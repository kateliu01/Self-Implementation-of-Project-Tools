#ifndef _DECORATOR_H
#define _DECORATOR_H
#include<string>
#include"beverage.h"
class Decorator : public Beverage{
public:
    Beverage* decor_bev;
    virtual std::string getDescription()=0;
    virtual float getPrice()=0;
};
#endif