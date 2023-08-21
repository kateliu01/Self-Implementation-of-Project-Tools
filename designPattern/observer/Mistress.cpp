#include<iostream>
#include"Mistress.h"
void Mistress::check(){
    std::cout <<"Mistress::checking..."<< std::endl;
}
void Mistress::doAction() {
    this->check();
}