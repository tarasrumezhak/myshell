#include <iostream>
#include <boost/program_options.hpp>
#include <sys/wait.h>
#include "operations/operations.hpp"

#define MAXDIR 4096


char* get_cwd() {
//    char buf[4096];
//    getcwd(buf, 4096);
//    return buf;

    char dir[MAXDIR];
    char *result = getcwd(dir, MAXDIR);
    //printf("Current directory is %s", dir);
    return result;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

//std::string preprocess_line(std:: string line) {
//
//}


int main(int argc, char **argv) {
//    std::cout << get_cwd() << '$';
    while(true) {
        std::cout << get_cwd() << '$';
        std::string line;
        std::getline (std::cin,line);
        std::cout << "You entered: " << line << "\n";

        std::istringstream ss(line);
        std::string token;

        std::vector<std::string> args;

        while(std::getline(ss, token, ' ')) {
            std::cout << token << '\n';
            args.push_back(token);
        }

        std::string victim_name(args[0]);

        auto path_ptr = getenv("PATH");
        std::string path_var;
        if(path_ptr != nullptr)
            path_var = path_ptr;
        path_var += ":.";
        setenv("PATH", path_var.c_str(), 1);

        std::vector<const char*> arg_for_c;
        for(auto s: args)
            arg_for_c.push_back(s.c_str());
        arg_for_c.push_back(nullptr);

        pid_t parent = getpid();
        pid_t pid = fork();

        if (pid == -1)
        {
            std::cerr << "Failed to fork()" << std::endl;
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            // We are parent process
//            std::cout << "Parent: Hello from parent" << std::endl;
//            std::cout << "Parent: Parent PID: " << parent << ", child PID: " << pid << std::endl;
            int status;
            waitpid(pid, &status, 0);
//            std::cout << "Parent: child stopped, exit code: " << status << std::endl;
        }
        else
        {
            // We are the child
//            execve(victim_name.c_str(), args, environ);
            std::cout << "\t running " << line << std::endl;

//            std::string to_exec = "usr/bin/" + victim_name;

            execvp(victim_name.c_str(), const_cast<char* const*>(arg_for_c.data()));
//            std::cerr << "Parent: Failed to execute " << victim_name << " \n\tCode: " << errno << std::endl;
            exit(EXIT_FAILURE);   // exec never returns
        }

    }
    return 0;

}
