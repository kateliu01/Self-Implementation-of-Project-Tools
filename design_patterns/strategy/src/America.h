#ifndef _AMERICA_H
#define _AMERICA_H
#include"Strategy.h"
#define AMERICA_RATE 0.1403
class America : public Strategy{
    public:
        float doCalcute(float rmb) {
            return rmb*AMERICA_RATE;
        }
};
#endif