#ifndef _SUBJECT_H
#define _SUBJECT_H
#include "Observer.h"
#include <list>
class Subject{
    private:
	// 编译时用父类指针  运行时传具体子类指针
	    std::list <Observer*> listener;
    public:
        void attach(Observer* o){
            listener.emplace_back(o);
        }
        void detath(Observer* o) {
            listener.remove(o);
        }
        void Notify() {
            for(auto it=listener.begin(); it!=listener.end(); it++) {
                // 迭代器是指针，获得元素要*it啊！
                (*it)->doAction();
            }
        }
};
#endif
