
#include<bits/stdc++.h>
using namespace std;
// 第一次实现对象池
// 单线程下
template<typename T>
class ObjectPool{
public:
    ObjectPool(){}
    ObjectPool(int s):max_size(s) {
        isfull = false;
        // 创建对象
        while(s--) {
            T* t = new T();
            canUse.emplace_back(t);
        }
    }
    bool isFull() {
        return isfull;
    }
    // bool resetObj() {
    //     //  这是一个虚函数，所有放入对象池的对象都需要实现这个函数
    // }
    T* getObj() {
        if (isfull) return nullptr;
        else {
            T* tmp = canUse.front();
            canUse.pop_front();
            inUse.emplace_back(tmp);
            isfull = (canUse.size() == 0);
            return tmp;
        }
    }
    // 用了二级指针，因为要修改指针
    void retuObj(T** t) {
        auto iter = std::find(inUse.begin(), inUse.end(),*t);
        inUse.erase(iter);
        canUse.emplace_back(*t);
        //  我觉得很重要的一点是：要使t失效叭
        *t=nullptr;
        isfull = (canUse.size() == 0);
    }
private:
    int max_size;
    bool isfull;
    // 放的是对象，不是对象指针！
    list<T*> canUse, inUse;
};
class People{
public:
    string name;
    People(string s):name(s){}
    People(){}
};
int main(){
    ObjectPool<People> pool(2);
    People* p1 = pool.getObj();
    People* p2 = pool.getObj();
    p1->name = "alice";
    p2->name = "jack";
    cout << (void*)p1 << endl;
    cout << (void*)p2<< endl;
    pool.retuObj(&p1); 
    pool.retuObj(&p2);
    People* p3 = pool.getObj();
    cout << (void*)&(*p3) << endl;
    return 0;
}
