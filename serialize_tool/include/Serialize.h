#ifndef _SERIALIZE_H
#define _SERIALIZE_H

//类的前向声明，因为很明确，我不想DataStream和Serialize谁继承谁，只是互相调用一下类方法，所以很适合用类的前向声明
// 这里不需要引用#include"DataStream.h"
class DataStream;

// 不需要继承DataStream
class Serialize{
public:
    virtual bool serialize(DataStream& ds) const =0;
    virtual bool unserialize(DataStream& ds)=0;
};
#endif