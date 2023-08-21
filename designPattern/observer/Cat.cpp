#include<iostream>
#include"Cat.h"
void Cat::miaow(){
    std::cout << "Cat::miaowing..." << std::endl;
}

void Cat::doAction() {
    miaow();
}