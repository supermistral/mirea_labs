#ifndef _CHILD_H
#define _CHILD_H
#include "base.h"

class Child : public Base {
public:        
    using Base::Base;

    void methodSignal(std::string&);
    void methodHandler(Base*, std::string);
};

#endif