#ifndef _KID_H
#define _KID_H
#include "Observer.h"
class Kid: public Observer{
    public:
        void crying();
        virtual void doAction();
};
#endif