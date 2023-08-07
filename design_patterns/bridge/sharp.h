#ifndef _SHARP_H
#define _SHARP_H
#include "filter.h"
#include <iostream>
class Sharp : public Filter{
public:
    void filter_algorithm() {
        std::cout << "sharp filter"<<std::endl; 
    }
};
#endif