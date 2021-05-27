#ifndef _CHILD2_H
#define _CHILD2_H
#include "base.h"

class Child2 : public Base {
public:
    using Base::Base;

    void methodSignal(std::string&);
    void methodHandler(std::string);
};

#endif