//下面是C++使用管道（Pipe）进行进程间通信的一个例子：
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    int fd[2];
    pid_t pid;
    char buffer[256];

    // 创建管道
    if (pipe(fd) < 0) {
        cerr << "Failed to create pipe." << endl;
        return 1;
    }
    
    // 创建子进程
    if ((pid = fork()) < 0) {
        cerr << "Failed to create child process." << endl;
        return 1;
    } else if (pid > 0) { // 父进程
        close(fd[0]); // 关闭读端
    
        string message = "Hello, child process.";
        write(fd[1], message.c_str(), message.length()); // 向管道写入数据
    
        wait(NULL); // 等待子进程结束
    } else { // 子进程
        close(fd[1]); // 关闭写端
    
        read(fd[0], buffer, sizeof(buffer)); // 从管道读取数据
        cout << "Message from parent process: " << buffer << endl;
    }
    
    return 0;

}
