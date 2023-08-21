#ifndef _PNG_H
#define _PNG_H
#include "image.h"
#include<string>
#include<iostream>
class Png : public Image{
public:
    Png(){}
    Png(Filter* f): Image(f){}
    virtual void addFilter() {
        std::cout << ".png add ";
        img_fiter->filter_algorithm();
    }  
};
#endif