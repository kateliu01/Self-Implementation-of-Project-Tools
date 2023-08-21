// 循环引用到底是个什么问题？

#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include <memory>
using namespace std;
class B;                 // 前向声明！
class A {
public:
    shared_ptr<B> ptr;
};
class B {
public:
    shared_ptr<A> ptr;
};
int main() {
    shared_ptr<A> a_ptr = make_shared<A>();
    shared_ptr<B> b_ptr = make_shared<B>();
    a_ptr->ptr = b_ptr;
    b_ptr->ptr = a_ptr;
    return 0;
}

// a_ptr 和 b_ptr都不会得到释放！


/* 
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include <memory>
using namespace std;
class B;
class A {
public:
    weak_ptr<B> ptr;
};
class B {
public:
    weak_ptr<A> ptr;
};
int main() {
    shared_ptr<A> a_ptr = make_shared<A>();
    shared_ptr<B> b_ptr = make_shared<B>();
    a_ptr->ptr = b_ptr;
    b_ptr->ptr = a_ptr;
    return 0;
}

// 这样才可以释放
*/

/*

#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include <memory>
using namespace std;
class B;
class A {
public:
    shared_ptr<B> ptr;
};
class B {
public:
    shared_ptr<A> ptr;
};
int main() {
    shared_ptr<A> a_ptr = make_shared<A>();
    shared_ptr<B> b_ptr = make_shared<B>();
    a_ptr->ptr = b_ptr;
    b_ptr->ptr = a_ptr;
    a_ptr->ptr = nullptr;
    return 0;
}
//或者你手动置nullptr



*/
