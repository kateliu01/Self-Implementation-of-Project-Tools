#include<iostream>
#include"App.h"
using namespace std;
int main() {
    Lib* myapp = new App();
    myapp->run();
    delete(myapp);
    return 0;
}