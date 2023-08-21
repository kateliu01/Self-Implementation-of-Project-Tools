#ifndef _PNGFACTORY_H
#define _PNGFACTORY_H
#include<iostream>
#include "ImageFactory.h"
class PngFactory : public ImageFactory{
    public:
        // 要返回具体对象
        ImageFactory* create(){
            return new PngFactory();
        }  
        void read() {
            std::cout << "read png algorithm" << std::endl;
        }
};
#endif