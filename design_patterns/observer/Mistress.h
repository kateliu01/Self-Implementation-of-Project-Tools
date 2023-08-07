#ifndef _MISSTRESS_H
#define _MISSTRESS_H
#include"Observer.h"
class Mistress : public Observer{
    public:
        void check();
        virtual void doAction();
};
#endif