#include"Dog.h"
#include<iostream>
void Dog::bark(){
    std::cout << "Dog::barking..." << std::endl;
}

void Dog::doAction(){
    Dog::bark();
}