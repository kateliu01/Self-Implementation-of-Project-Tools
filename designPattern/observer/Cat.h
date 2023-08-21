#ifndef _CAT_H
#define _CAT_H
#include"Observer.h"
class Cat: public Observer{
    public:
        void miaow();
        virtual void doAction();
};
#endif