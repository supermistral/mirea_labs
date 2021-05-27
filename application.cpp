#include <iostream>
#include "base.h"
#include "child.h"
#include "child2.h"
#include "child3.h"
#include "child4.h"
#include "child5.h"
#include "application.h"


Application::Application(Base* parentObj) : Base(parentObj, "") {
};

void Application::build_tree_objects() {        
    std::string name1, name2;        
    std::cin >> name1;        
    this->setName(name1);
    Base *tempRoot = this;
    Base *tempChild = 0;
    
    for (;;) {
        std::cin >> name1 >> name2;
        if (name1 == name2)
            break;
        if (tempRoot->getName() != name1)
            tempRoot = tempChild;
        tempChild = new Child(tempRoot, name2);
    }
}

void Application::exec_app() {        
    std::cout << this->getName();        
    this->printTree();
}

void Application::new_build_tree_objects() {        
    std::string name1, name2;        
    std::cin >> name1;        
    int valReady, valClass;        
    this->setName(name1);        
    this->setReady(1);        
    Base *tempRoot = this;        
    Base *tempChild = 0;        
    
    for (;;) {                
        std::cin >> name1;
        if (name1 == "endtree")
            break;
        std::cin >> name2 >> valClass >> valReady;
        tempRoot = this->getObject(name1);
        
        if (valClass == 2)
            tempChild = new Child(tempRoot, name2);
        else if (valClass == 3)
            tempChild = new Child2(tempRoot, name2);
        else                        
            tempChild = new Child3(tempRoot, name2);
        tempChild->setReady(valReady);
    }
}; 

void Application::new_exec_app() { 
    std::cout << "Test result\n";        
    this->printReadyTree(); 
}; 

void Application::new_build_tree_objects_ver2() { 
    std::string name1, name2;        
    std::cin >> name1;        
    int valReady, valClass;        
    this->setName(name1);        
    this->setReady(1);        
    Base* tempRoot = this;        
    Base* tempChild = 0;        

    for (;;) { 
        std::cin >> name1;
        if (name1 == "endtree")
            break;                
        std::cin >> name2 >> valClass >> valReady;
        tempRoot = this->getObject(name1);
        //tempRoot = this->getObjectByCoord(name1.substr(1));
        
        switch (valClass) { 
        case 2:
            tempChild = new Child(tempRoot, name2);
            break;
        case 3:
            tempChild = new Child2(tempRoot, name2); 
            break;                        
        case 4:                                
            tempChild = new Child3(tempRoot, name2);
            break;                        
        case 5:
            tempChild = new Child4(tempRoot, name2);
            break;                        
        default:                                
            tempChild = new Child5(tempRoot, name2); 
        }  

        tempChild->setReady(valReady);
        tempChild->setNumber(valClass);
    } 
}; 

void Application::new_exec_app_ver2() { 
    std::cout << "Object tree\n";        
    this->printModelTree(0);
    this->coordRouting();
};

void Application::coordRouting() {
    std::string coord;
    Base* obj = nullptr;

    for (;;) {
        std::cin >> coord;
        if (coord == "//")
            break;

        if (coord.substr(0, 2) == "//")
            obj = this->getObject(coord.substr(2));
        else
            obj = this->getObjectByCoord(coord.substr(1));

        if (obj)
            std::cout << "\n" << coord << " Object name: " << obj->getName();
        else
            std::cout << "\n" << coord << " Object not found";
    }
};

void Application::methodSignal(std::string& msg) {
    msg = " Text: " + this->getName() + " -> " + msg;
};

void Application::methodHandler(std::string msg) {
    std::cout << "\nSignal to " << this->getName() + msg;
};

void Application::fillConnections() {
    std::string numConnection, senderName, handlerName;
    Base* sender = nullptr;
    Base* handler = nullptr;
    
    std::cout << "\nSet connects";
    for (;;) {
        std::cin >> numConnection;
        if (numConnection == "0")
            break;

        std::cin >> senderName >> handlerName;
        sender = this->getObject(senderName);
        handler = this->getObject(handlerName);
        sender->setConnect(
            this->getMethodSignal(sender->getNumber()),
            handler,
            this->getMethodHandler(handler->getNumber())
        );

        std::cout << "\n" << numConnection << " " << senderName << " " << handlerName;
    }
};

void Application::runSignals() {
    std::string senderName, msg;
    Base* sender = nullptr;

    std::cout << "\nEmit signals";
    for (;;) {
        std::cin >> senderName;
        if (senderName == "endsignals")
            break;

        std::cin >> msg;
        sender = this->getObject(senderName);
        sender->emitSignal(
            this->getMethodSignal(sender->getNumber()),
            msg
        );
    }
};

SignalType Application::getMethodSignal(int numClass) {
    switch (numClass) {
    case 1:
        return SIGNAL(Application, methodSignal);
    case 2:
        return SIGNAL(Child, methodSignal);
    default:
        return SIGNAL(Child2, methodSignal);
    }
};

HandlerType Application::getMethodHandler(int numClass) {
    switch (numClass) {
    case 1:
        return HANDLER(Application, methodHandler);
    case 2:
        return HANDLER(Child, methodHandler);
    default:
        return HANDLER(Child2, methodHandler);
    }
};

void Application::new_exec_app_ver3() {
    std::cout << "Object tree\n";
    this->printModelTree(0);
    this->fillConnections();
    this->runSignals();
};