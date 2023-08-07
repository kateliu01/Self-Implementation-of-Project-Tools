#ifndef _ADDICE_H
#define _ADDICE_H
#include<string>
#include"decorator.h"
class Ice: public Decorator{
public:
    std::string des =" add Ice";
    float price = 2;
    Ice(Beverage* be){
        this->decor_bev = be;
    }
    std::string getDescription(){return decor_bev->getDescription()+des;}
    float getPrice(){return decor_bev->getPrice()+price;}
};
#endif