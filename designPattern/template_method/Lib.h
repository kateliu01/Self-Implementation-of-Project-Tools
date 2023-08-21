#ifndef _Lib_H
#define _Lib_H
#include<iostream>
class Lib {
public:
   void run();
   virtual void step1()=0;
   virtual void step2()=0;
};
#endif