#include"Cat.h"
#include"Kid.h"
#include"Mouse.h"
#include"Subject.h"
#include"Observer.h"
#include"Mistress.h"
#include"Dog.h"
int main() {
    Mouse* sub = new Mouse();
    Cat* o1 = new Cat();
    Kid* o2 = new Kid();
    Mistress* o3 = new Mistress();
    Dog * o4 = new Dog();
    sub->attach(o1);
    sub->attach(o2);
    // sub->attach(o3);
    // sub->attach(o4);
   
    sub->running();
   
    sub->detath(o1);
    sub->detath(o2);
    // sub->detath(o3);
    // sub->detath(o4);
    delete(sub);
    delete(o1);
    delete(o2);
    delete(o3);
    delete(o4);
    return 0;
}
