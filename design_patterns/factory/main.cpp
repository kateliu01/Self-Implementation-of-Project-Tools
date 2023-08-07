/*
    实现一个图片读取器ImageReader，图片有多种格式，jpg，png等
    ImageFactory类是  工厂类，作为接口，给ImageReader用
    PngFactory类  是具体工厂类，继承工厂类，返回一个Png对象&提供Png的读取方法
    JpgFactory类  是具体工厂类，继承工厂类，返回一个Jpg对象&提供Jpg的读取方法
*/
#include "ImageReader.h"
#include "ImageFactory.h"
#include "PngFactory.h"
using namespace std;
int main(){
    ImageFactory* png = new PngFactory();
    // 在这犯傻半天.....
    // ImageReader* reader(png);
    ImageReader* reader = new ImageReader(png);
    reader->read();
    return 0;
}
