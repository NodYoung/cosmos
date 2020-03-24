//
// Created by liyanan on 3/24/20.
//

#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void signal_handler(int signum) {
    cout << "Interrupt signal (" << signum << ") received. \n";
    // cleanup and close up stuff here
    // terminate program
    exit(signum);
}

class Cls {
public:
    Cls(std::string s):s_(s) {};
    ~Cls() { std::cout << "Cls:" << s_ << std::endl;}
    std::string s_;
};

Cls a("a");

int main() {
    // register signal SIGINT and signal handler
    signal(SIGINT, signal_handler);
//    signal(SIGTERM, signal_handler);
    Cls b("b");
    while(1) {
        cout << "Going to sleep ..." << endl;
        sleep(1);
    }
//    std::raise(SIGTERM);
    return 0;
}