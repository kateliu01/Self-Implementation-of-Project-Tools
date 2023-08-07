#ifndef _BLUR_H
#define _BLUR_H
#include"filter.h"
#include<iostream>
class Blur :  public Filter{
    public:
        void filter_algorithm(){
            std::cout << "blur filter" << std::endl;
        }
};
#endif