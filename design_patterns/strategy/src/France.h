#ifndef _FRANCE_H
#define _FRANCE_H
#include"Strategy.h"
#define FRANCE_RATE 0.1305
class France : public Strategy{
    public:
        float doCalcute(float rmb) {
            return rmb*FRANCE_RATE;
        }
};
#endif