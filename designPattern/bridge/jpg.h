#ifndef _JPG_H
#define _JPG_H
#include "image.h"
#include<string>
#include<iostream>
class Jpg : public Image{
    public:
        // 以下写法是错的....
        // Filter* img_fiter;
        // // 子类仍然要写自己构造函数，这个是遗传的，父类只有Image()
        // Jpg(Filter* f): img_fiter(f) {}

        // 不能使用初始话列表！只能在{}里用this赋值！
        Jpg(){}
        Jpg(Filter* f): Image(f){}
        virtual void addFilter() {
            std::cout << ".jpg add ";
            img_fiter->filter_algorithm();
        } 
};
#endif