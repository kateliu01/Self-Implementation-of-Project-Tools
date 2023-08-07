#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>

const char* PIPE_PATH = "/tmp/my_named_pipe";

void parentProcess() {
    int fd = open(PIPE_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    std::string message = "Hello from parent!";
    write(fd, message.c_str(), message.size());

    close(fd);
}

void childProcess() {
    int fd = open(PIPE_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    char buffer[256];
    int bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
        std::string message(buffer, bytesRead);
        std::cout << "Child received: " << message << std::endl;
    }

    close(fd);
}

int main() {
    // Create the named pipe
    mkfifo(PIPE_PATH, 0666);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        childProcess();
    } else {
        // Parent process
        parentProcess();
    }

    // Remove the named pipe
    unlink(PIPE_PATH);

    return 0;
}
