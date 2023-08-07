#ifndef _A_H
#define _A_H
#include"Serialize.h"
#include"DataStream.h"
/*
    DataStream类是实现序列化的主体类，Serialize类是DataStream的接口类
    任何想要实现序列化的自定义类，都要继承Serialize接口类，
    接口类的作用是提供函数给子类，
    例如Serialize的类方法serialize和unserialize，其中肯定要用到DataStream的功能
    即Serialize类要用到DataStream的功能，可以Serialize类继承DataStream， 也可以Serialize类包含一个DataStream对象
    避免再继承，Serialize类可以直接用一个DataStream对象
*/
#include <vector>
class A : public Serialize {
private:
    int age;
    std::string name;
public:
    A(){}
    A(std::string n, int a):name(n), age(a){}
    ~A(){}
    // 要实现Serialize的纯虚函数
    virtual bool serialize(DataStream& ds) const{
        // 先写class
        // 这个type并不是字符'5'，而是ascii=5的字符
        char type = DataStream::datatype::CLASS;
        ds.write((char*)&type, sizeof(char));
     
        // ds.write(name);
        // ds.write(age);
        // 可变参数实现
        ds.write_args(name, age);
      
        return true;
    }
    virtual bool unserialize(DataStream& ds){
        char type;
        ds.read((char*) &type, sizeof(char));
        std::cout << type;
        std::cout << DataStream::datatype::CLASS ;
        if ((DataStream::datatype)type != DataStream::datatype::CLASS) return false;
        // ds.read(name);
        // ds.read(age);
        // 可变参数实现
        ds.read_args(name, age);
        return true;
    }
    
        // 可变参数
    void write(const Serialize& a);
    bool read(Serialize& a);
    
};
#endif