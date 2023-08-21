#ifndef _ADDBUBBLE_H
#define _ADDBUBBLE_H
#include<string>
#include"decorator.h"
class Bubble : public Decorator{
public:
    std::string des =" add bubble";
    float price = 3;
    Bubble(Beverage* be){
        this->decor_bev = be;
    }
    std::string getDescription(){return decor_bev->getDescription()+des;}
    float getPrice(){return decor_bev->getPrice()+price;}
};
#endif