#ifndef _JPGFACTORY_H
#define _JPGFACTORY_H
#include <iostream>
#include "ImageFactory.h"
#include ""
class JpgFactory : public ImageFactory {
    public:
        virtual ImageFactory* create(){
            return new JpgFactory();
        }
        virtual void read() {
            std::cout << "read jpg algorithm" << std::endl;
        }
};
#endif