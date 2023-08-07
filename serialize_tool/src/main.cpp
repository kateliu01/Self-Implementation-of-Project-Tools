#include"DataStream.cpp"
#include"A.h"
using namespace std;
int main() {
    DataStream ds;
    // int old_1 = 1000, new_1;
    // string old_2 = "ajdfhjdskhfjdkS", new_2;
    // ds << old_1 << old_2;
    // ds >> new_1 >> new_2;

    // vector<int> v ={1,2,3,4}, v2;
    // ds << v;
    // ds >> v2;


    // list<int> v ={1,2,3,4}, v2;
    // ds << v;
    // ds >> v2;

    // map<int, string> m1, m2;
    // m1[1]="a";
    // m1[2]="b";
    // ds<<m1;
    // ds>>m2;

    A a1("kate", 9), a2;
    ds<<a1;
    ds.saveFile();
    ds>>a2;
    ds.loadFile();
    ds >> a2;
    return 0;
}

