#include"Calculator.h"
#include"Strategy.h"
#include"America.h"
#include"France.h"
#include<iostream>
float Calculator::calculatePrice(float rmb) {
    // Strategy* s = new America();
    Strategy* s = new France();
    float money = s->doCalcute(rmb);
    std::cout << "money:" << money << std::endl;
    delete(s);
    return money;
}