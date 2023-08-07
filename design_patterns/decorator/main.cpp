#include"beverage.h"
#include"coffee.h"
#include"milk.h"
#include"addBubble.h"
#include"addIce.h"
#include <iostream>

int main() {
    Beverage* order1 = new Milk();
    std::cout << order1->getDescription() << std::endl;
    order1 = new Bubble(order1);
    std::cout <<order1->getDescription()<< std::endl;
    std::cout <<order1->getPrice()<< std::endl;

    Beverage* order2 = new Coffee();
    std::cout <<order2->getDescription()<< std::endl;
    order2 = new Ice(order2);
    std::cout <<order2->getDescription()<< std::endl;
    std::cout <<order2->getPrice()<< std::endl;


    delete(order1);
    delete(order2);
    return 0;
}