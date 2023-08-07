#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main() {
    int fd[2];
    pid_t p;
    char buffer[256];
    if (pipe(fd) < 0) {
        // 基于fd数组创建半双工的管道
        cerr << "fail to create pipe" << std::endl;
        return 1;
    }
    // 尝试创建子进程
    // if(p = fork() < 0) {     // 原来一直在这出错，你这样直接
    if((p = fork()) < 0) {
        // 创建失败
        cerr << "fail to create newProcess" << std::endl;
        // 原来这没return 1;
        return 1;
    }
    // 在父进程中，p的值为新进程的id
    else if (p>0) {
        // 此时的进程是 父进程
        // 父进程写数据
        // 关闭读端
        close(fd[0]);
        // char messg[] = "hello";
        // write(fd[1], messg, sizeof(messg)-1);
        string messg = "Hello, child process.";
        write(fd[1], messg.c_str(), messg.length()); // 向管道写入数据
        // 这里居然需要等待子进程结束....
        wait(NULL);
        
    }
    else {
        // 此时在子进程中
        // 关闭写端
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        cout << "Messg from father Process:" << buffer << endl;
    }
    return 0;
}