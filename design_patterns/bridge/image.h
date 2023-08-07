#ifndef _IMAGINE_H
#define _IMAGINE_H
#include"filter.h"
class Image{
    public:
        Filter* img_fiter=nullptr;
        float width;
        float height;

        // Image(Filter* f): img_fiter(f) {}
        Image(){}
        Image(Filter* f):img_fiter(f) {}
        // 图片选择加滤镜
        virtual void addFilter()=0; 
};
#endif
