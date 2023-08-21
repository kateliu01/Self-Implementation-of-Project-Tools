#include<iostream>
#include"image.h"
#include"filter.h"
#include"png.h"
#include"jpg.h"
#include"blur.h"
#include"sharp.h"
using namespace std;
int main(){
    Filter* blr_fil = new Blur();
    Image* img = new Png(blr_fil);
    img->addFilter();


    Filter* shp_fil = new Sharp();
    Image* img2 = new Jpg(shp_fil);
    img2->addFilter();

    delete blr_fil;
    delete img;
    delete img2;
    delete shp_fil;
    return 0;
}