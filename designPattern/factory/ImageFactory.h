#ifndef _IMAGEFACTORY_H
#define _IMAGEFACTORY_H
class ImageFactory{
    public:
        // 工厂是用来生产产品(对象)的
        virtual ImageFactory* create()=0;
        // 读取图片
        virtual void read()=0;
};
#endif