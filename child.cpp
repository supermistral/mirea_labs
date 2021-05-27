#include "child.h"
#include <iostream>


void Child::methodSignal(std::string& msg) {
    msg = " Text: " + this->getName() + " -> " + msg;
};

void Child::methodHandler(Base* obj, std::string msg) {
    std::cout << "\nSignal to" << obj->getName() + msg;
};