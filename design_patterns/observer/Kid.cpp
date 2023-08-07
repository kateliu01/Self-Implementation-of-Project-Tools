#include<iostream>
#include"Kid.h"
void Kid::crying() {
    std::cout << "Kid::cring..." << std::endl;
}

void Kid::doAction() {
    crying();
}