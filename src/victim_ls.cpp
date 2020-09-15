#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
extern char **environ;


int main() {
    pid_t parent = getppid();
    pid_t pid = getpid();
//    std::cout << "Child: Hello from child!" << std::endl;
//    std::cout << "Child: Parent PID: " << parent << ", child PID: " << pid << endl;
//    std::cout << "And now running ls: " << endl;
    system("ls");
    return 0;
}