#include"DataStream.h"
#include<algorithm>
#include<math.h>
#include<string.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
    /*
        对于每个序列化对象，需要记录它的TLV,
        写buffer三次
        write作为基础成员函数，形参限定写入buffer的条件，例如，地址和大小
        写Type的时候，对象是enum的datatype[INT]=0, 形参：地址是&datatype[INT]，大小是1B（我规定enum的type都用1B存）
        写Len的时候，对象是size=4, 形参： 地址是&size, 大小是sizeof(int)
        写Value的时候，对象是data，形参：地址是&data，大小是sizeof(int)
    */
void DataStream::show_bytes() const{
    int size = buffer.size();
    std::cout  << "data_size:" << size << std::endl;
}
void DataStream::write(const char* addr, int len) {
    // 后期可以在这优化一下buff的扩容机制
    // 上次序列化的结尾
    int last = buffer.size();
    // 手动扩容
    // buff初始化，避免capacity过大
    buffer.resize(last + len);
    // 这儿应该resize吧！
    // buffer.reserve(last + len);
    // 将char*拷贝到buff的size之后
    // void *memcpy(void *destin, void *source, unsigned n)；
    // destin-- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
    // source-- 指向要复制的数据源，类型强制转换为 void* 指针。
    // n-- 要被复制的字节数。
    memcpy(&buffer[last], addr, len);
}

// 基础read方法
void DataStream::read(char* adr, int len){
    // 读出len字节
    memcpy(adr, (char*)&buffer[pos], len);
    pos += len;
}
// 大小端检测
DataStream::Endian DataStream::checkEndian() {
    int a = 0x12345678;
    char add[4];
    memcpy(add, &a, 4);
    if (add[0] == 0x78) return Endian::LITTLEENDIAN;
    else return Endian::BIGENDIAN;
}

void DataStream::saveFile() {
    std::ofstream f("../file/1.txt");
    for(int i=0; i<buffer.size(); i++)
        f << buffer[i];
    f.close();
}
void DataStream::loadFile() {
    std::ifstream f("../file/1.txt");
    // read ( char * buffer, streamsize size );
    //这里 buffer 是一块内存的地址，用来存储或读出数据。参数size 是一个整数值，表示要从缓存（buffer）中读出或写入的字符数(size值很重要，因为二进制文件内容没有行的概念(’\n’)，字节之间是紧挨着的)。
    // for(int i=0; i<buffer.size(); i++)
    //     f.read(&buffer[i], 1);
    // f.close(); 
    while(!f.eof())           // <==就是这里
    {
        char tmp;
        f.read((char *)&tmp, sizeof(tmp));
        buffer.emplace_back(tmp);
    }
    f.close(); 
}

// int
void DataStream::write(const int data) {
    // enum的value是int....你转char要 
    char type = datatype::INT  ;
    int data_size = sizeof(int);
    // 要写三次
    // 例如int，第一次写T，值是：datatype::INT        ，用1B就可以存储了（代表我最多支持256种基础类型）
    //         第二次写L，值是4B, int最多32位数，2^6=64, 用1B绰绰有余可以表示 32 
    //         第三次记录V，值是data，最多需要4B存储
    if (byteOrder == Endian::BIGENDIAN) {
        char* beg = (char*)&data;
        char* end = beg+sizeof(int);
        // 反转高低地址
        std::reverse(beg, end);
    }
    write((char*) &type, 1);
    write((char*) &data_size, 1);
    write((char*) &data, data_size);
    // write((char*) &data, 4);  等价于上面一句话
}
bool DataStream::read(int& value){
    // 因为这可能要判断string内的int，所以写的是pos
    if(buffer[pos] != datatype::INT ) return false;
    // int 类型是 1+1+4
    pos+=2;
    // 将4B的char转成int.....
    value = *((int *)(&buffer[pos]));
    if (byteOrder == Endian::BIGENDIAN) {
        char* beg = (char*)&value;
        char* end = beg+sizeof(int);
        // 反转高低地址
        std::reverse(beg, end);
    }
    pos+=4;
    return true;
}
DataStream& DataStream::operator << (int a) {
    write(a);
    return *this;
}
DataStream& DataStream::operator >> (int& a) {
    read(a);
    return *this;
}


// string
void DataStream::write(const std::string str) {
    // string = T(1B) + L(int) + V
    char type = datatype::STRING  ;
    int data_size = str.size();
    write((char*) &type, 1);
    // 像存int那样存L，即1+1+4
    char type_int = datatype::INT ;
    write((char*) &(type_int), 1);
    write((char*) &data_size, 1);
    write((char*) &data_size, 4);
    // string 转 ...char*
    // 因为string中每个字符都要存储1B，所以直接是data_size
    write(str.data(), data_size);
}
bool DataStream::read(std::string& value){
    if(buffer[pos] != datatype::STRING ) return false;
    // string 类型是 1+L(int)+V
    // string的长度L是嵌套了一个int
    pos+=1;
    int len=0;
    read(len);
    // pos+=4;// 因为int是1+1+4   这个在int那加过了
    //2.一个字符串的子串赋值给另一个字符串 a.assign(b,begin,len);
    value.assign((char*)&buffer[pos], len);
    pos+=len;
    return true;
}
DataStream& DataStream::operator << (std::string a) {
    write(a);
    return *this;
}

DataStream& DataStream::operator >> (std::string& a){
    read(a);
    return *this;
}



// vector
template<typename T>
void DataStream::write(const std::vector<T> v) {
    // 存vector的时候
    //  Type(VECTOR, 1B) + L(INT, 1+1+4) + V(T,T,T,T....)
    char type = datatype::VECTOR ;
    int v_size = v.size();
    write((char *)&type, 1);
    // 存int
    char type_int = datatype::INT ;
    write((char*)&type_int, 1); 
    write((char*)&v_size, 1);
    write((char*)&v_size, 4);
    // 存T
    for(int i=0; i<v_size; i++) {
        // 会自己找重载....
        write(v[i]);
    }
}

template<typename T>
bool DataStream::read(std::vector<T>& v) {
    // T(1) + L(INT 1+1+4) + V(T,T,T...)
    if (buffer[pos] != datatype::VECTOR ) return false;
    pos++;
    int v_size=0;
    read(v_size);
    for(int i=0; i<v_size; i++) {
        T tmp;
        read(tmp);
        v.emplace_back(tmp);
    }
    return true;
}
template<typename T>
DataStream& DataStream::operator << (std::vector<T> v) {
    write(v);
    return *this;
}
template<typename T>
DataStream& DataStream::operator >> (std::vector<T>& v){
    read(v);
    return *this;
}



// list
template<typename T>
void DataStream::write(const std::list<T> a){
    // 存list的时候
    //  Type(LIST, 1B) + L(INT, 1+1+4) + V(T,T,T,T....)
    char type = datatype::VECTOR;
    int v_size = a.size();
    write((char *)&type, 1);
    // 存int
    char type_int = datatype::INT ;
    write((char*)&type_int, 1); 
    write((char*)&v_size, 1);
    write((char*)&v_size, 4);
    // 存T
    for(auto it=a.begin(); it!=a.end(); it++) {
        // 会自己找重载....
        write(*it);
    }
}
template<typename T>
bool DataStream::read(std::list<T>& a){
    // T(1) + L(INT 1+1+4) + V(T,T,T...)
    if (buffer[pos] != datatype::VECTOR) return false;
    pos++;
    int v_size=0;
    read(v_size);
   
    for(int i=0; i<v_size; i++) {
        T tmp;
        read(tmp);
        a.emplace_back(tmp);
    }
    return true;
}
template<typename T>
DataStream& DataStream::operator << (std::list<T> a){
    write(a);
    return *this;
} 
template<typename T>
DataStream& DataStream::operator >> (std::list<T>& a){
    read(a);
    return *this;
}




// map
template<typename K, typename V>
void DataStream::write(const std::map<K, V> a){
    // T(1B) L(int 1+1+4) V()
    //  Type(MAP, 1B) + L(INT, 1+1+4) + V(T,T,T,T....)
    char type = datatype::MAP;
    int v_size = a.size();
    write((char *)&type, 1);
    // 存int
    char type_int = datatype::INT;
    write((char*)&type_int, 1); 
    write((char*)&v_size, 1);
    write((char*)&v_size, 4);
    // 存T
    for(auto it=a.begin(); it!=a.end(); it++) {
        // 会自己找重载....
        write(it->first);
        write(it->second);
    }

}
template<typename K, typename V>
bool DataStream::read(std::map<K, V>& a){
    if (buffer[pos] != datatype::MAP) return false;
    pos++;
    int v_size=0;
    read(v_size);
    for(int i=0; i<v_size; i++) {
        K tmp1;
        V tmp2;
        read(tmp1);
        read(tmp2);
        a.emplace(tmp1, tmp2);
    }
    return true;
}
template<typename K, typename V>
DataStream& DataStream::operator << (std::map<K, V> a){
    write(a);
    return *this;
}  
template<typename K, typename V>
DataStream& DataStream::operator >> (std::map<K, V>& a){
    read(a);
    return *this;
}




// class
void DataStream::write(const Serialize& s) {
    s.serialize(*this);

}
bool DataStream::read(Serialize& s) {
    s.unserialize(*this);
}

DataStream& DataStream::operator << (const Serialize& s) {
    write(s);
    return *this;
}

DataStream& DataStream::operator >> (Serialize& s){
    read(s);
    return *this;
}


// 可变参数

// 出口
void DataStream::write_args() {}
bool DataStream::read_args() {}
template<typename Args1, typename ...Args2>
void DataStream::write_args(const Args1& args1, Args2&... args2) {
    // 注意这里
    write(args1);
    write_args(args2...);
}
template<typename Args1, typename ...Args2>
bool DataStream::read_args(Args1& args1, Args2&... args2) {
    // 注意这里
    read(args1);
    return read_args(args2...);
}
// template<typename T>
// DataStream& DataStream::operator << (std::vector<T> v) {
//     write(v);
//     return *this;
// }
// template<typename T>
// DataStream& DataStream::operator >> (std::vector<T>& v){
//     read(v);
//     return *this;
// }