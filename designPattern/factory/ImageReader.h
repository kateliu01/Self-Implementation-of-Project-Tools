#ifndef _IMAGEREADER_H
#define _IMAGEREADER_H
#include "ImageFactory.h"

class ImageReader{
    public:
        // 获取一个图片吧
        ImageFactory* img;
        ImageReader(){}
        // ImageReader(ImageFactory* i):img(i->create()){}
        ImageReader(ImageFactory* i){
            this->img = i;
        }
        //图片读取器是用来读取图片的
        void read() {
            img->create()->read();
        }
};
#endif