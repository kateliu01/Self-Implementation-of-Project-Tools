#ifndef _DATASTREAM_H
#define _DATASTREAM_H
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <fstream>
#include "Serialize.h"
class DataStream {
public:
    enum datatype{
        // 初始为0
        INT = 0,
        STRING,  // 1B   4B  变长
        VECTOR,
        LIST,
        MAP,
        CLASS
    };

    enum Endian{
        BIGENDIAN =0,
        LITTLEENDIAN
    };
    //上句定义了一个数据结构 datatype，跟 struct Node{..}的Node一样，所以以后用的是域+值datatype::INT
    /*
        对于每个序列化对象，需要记录它的TLV,
        写buffer三次
        write作为基础成员函数，形参限定写入buffer的条件，例如，地址和大小
        写Type的时候，对象是enum的datatype[INT]=0, 形参：地址是&datatype[INT]，大小是1B（我规定enum的type都用1B存）
        写Len的时候，对象是size=4, 形参： 地址是&size, 大小是sizeof(int)
        写Value的时候，对象是data，形参：地址是&data，大小是sizeof(int)
    */
    DataStream():pos(0), byteOrder(checkEndian()){}
    ~DataStream(){}
    void show_bytes() const;
    int getByte(const int len);
    // 基础write方法
    void write(const char* addr, int len);
    // 基础read方法
    void read(char* add, int len);
    // 大小端检测
    Endian checkEndian();
    // 保存本地文件
    void saveFile();
    void loadFile();

    // int
    void write(const int a);
    bool read(int& a);
    DataStream& operator << (int a);  
    DataStream& operator >> (int& a);


    // string
    void write(const std::string a);
    bool read(std::string& a);
    DataStream& operator << (std::string a);  
    DataStream& operator >> (std::string& a);



    // vector
    template<typename T>
    void write(const std::vector<T> a);
    template<typename T>
    bool read(std::vector<T>& a);
    template<typename T>
    DataStream& operator << (std::vector<T> a);  
    template<typename T>
    DataStream& operator >> (std::vector<T>& a);




    // list
    template<typename T>
    void write(const std::list<T> a);
    template<typename T>
    bool read(std::list<T>& a);
    template<typename T>
    DataStream& operator << (std::list<T> a);  
    template<typename T>
    DataStream& operator >> (std::list<T>& a);



    // map
    template<typename K, typename V>
    void write(const std::map<K, V> a);
    template<typename K, typename V>
    bool read(std::map<K, V>& a);
    template<typename K, typename V>
    DataStream& operator << (std::map<K, V> a);  
    template<typename K, typename V>
    DataStream& operator >> (std::map<K, V>& a);




    // class
    void write(const Serialize& a);
    bool read(Serialize& a);
    // woc, 形参必须要加引用才行。
    // DataStream& operator << (Serialize a);  
    DataStream& operator << (const Serialize& a);  
    DataStream& operator >> (Serialize& a);

    // 可变参数
    void write_args();
    bool read_args();
    template<typename Args1, typename ...Args2>
    void write_args(const Args1& args1, Args2&... args2);
    template<typename Args1, typename ...Args2>
    bool read_args(Args1& args1, Args2&... args2);


private:
    std::vector<char> buffer;
    int pos;
    Endian byteOrder;
};

#endif
