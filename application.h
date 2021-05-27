#ifndef _APPLICATION_H
#define _APPLICATION_H
#include "base.h"

class Application : public Base {
public:        
    Application(Base*);

    void build_tree_objects();        
    void exec_app();

    void new_build_tree_objects();        
    void new_exec_app();

    void new_build_tree_objects_ver2();        
    void new_exec_app_ver2();

    void coordRouting();

    void methodSignal(std::string&);
    void methodHandler(std::string);
    void fillConnections();
    void runSignals();
    SignalType getMethodSignal(int);
    HandlerType getMethodHandler(int);
    void new_exec_app_ver3();
};

#endif