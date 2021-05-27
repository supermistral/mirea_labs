#include "child.h"
#include <iostream>


void Child::methodSignal(std::string& msg) {
    msg = " Text: " + this->getName() + " -> " + msg;
};

void Child::methodHandler(std::string msg) {
    std::cout << "\nSignal to " << this->getName() + msg;
};