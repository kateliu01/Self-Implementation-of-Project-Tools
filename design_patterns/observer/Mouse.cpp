#include<iostream>
#include"Mouse.h"
void Mouse::running(){
    std::cout << "Mouse::running!" << std::endl;
    Notify();
}
