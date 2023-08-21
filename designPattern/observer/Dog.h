#ifndef _DOG_H
#define _DOG_H
#include"Observer.h"
class Dog : public Observer{
    public:
        void bark();
        virtual void doAction();
};
#endif