#include "child2.h"
#include <iostream>


void Child2::methodSignal(std::string& msg) {
    msg = " Text: " + this->getName() + " -> " + msg;
};

void Child2::methodHandler(std::string msg) {
    std::cout << "\nSignal to " << this->getName() + msg;
};