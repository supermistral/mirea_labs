#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "base.h"

Base::Base(Base *parentObj, std::string nameObj)
    : parent(parentObj), name(nameObj) {        
    
    if (parent != 0)                
        parent->listChildren.push_back(this);
};

Base::~Base() {        
    for (size_t i = 0; i < listChildren.size(); ++i)
        delete listChildren[i];

    for (size_t i = 0; i < connections.size(); ++i)
        delete connections[i];
};

void Base::setName(std::string nameObj) {
    name = nameObj;
};

std::string Base::getName() {        
    return name;
};

void Base::printTree() { 
    std::cout << "\n" << name;        
    for (size_t i = 0; i < listChildren.size(); ++i)
        std::cout << "  " << listChildren[i]->getName();
    if (listChildren.back()->listChildren.size() != 0)
        listChildren.back()->printTree(); 
}; 

void Base::setParent(Base* parentObj) { 
    parent->listChildren.erase(
        std::remove(
            parent->listChildren.begin(), 
            parent->listChildren.end(), 
            this
        ), 
        parent->listChildren.end()
    );        
    parent = parentObj;        
    parent->listChildren.push_back(this); 
}; 

Base* Base::getParent() { 
    return parent; 
}; 

Base* Base::getObject(std::string nameObj) { 
    Base* obj = nullptr;
    if (name == nameObj)
        obj = this;
    else { 
        for (size_t i = 0; i < listChildren.size(); ++i) { 
            obj = listChildren[i]->getObject(nameObj);
            if (obj != nullptr)
                break; 
        } 
    }        
    return obj; 
}; 

void Base::printReadyTree() { 
    std::cout << "The object " << name;
    if (this->getReady() > 0)
        std::cout << " is ready";
    else                
        std::cout << " is not ready";
    for (size_t i = 0; i < listChildren.size(); ++i) { 
        std::cout << "\n";
        listChildren[i]->printReadyTree(); 
    } 
}; 

void Base::setReady(int value) {
    ready = value;
}; 

int Base::getReady() { 
    return ready; 
}; 

void Base::printModelTree(int offset) { 
    std::cout << std::setw(4 * (offset + 1)) << "" << name;
    
    for (size_t i = 0; i < listChildren.size(); ++i) { 
        std::cout << "\n";
        listChildren[i]->printModelTree(offset + 1); 
    } 
};

Base* Base::getObjectByCoord(std::string coord) {
    if (coord == name)
        return this;

    size_t ind = coord.find("/");
    if (ind == std::string::npos)
        return nullptr;

    Base* obj = this->getObjectByCoord(coord.substr(0, ind));
    if (!obj)
        return nullptr;

    coord = coord.substr(ind + 1);
    for (size_t i = 0; i < listChildren.size(); ++i) {
        obj = listChildren[i]->getObjectByCoord(coord);
        if (obj)
            break;
    }

    return obj;
};

void Base::setConnect(
    SignalType signal, 
    Base* objHandler, 
    HandlerType handler
) {
    for (Connection* conn : connections) {
        if (
            conn->signal == signal &&
            conn->objHandler == objHandler &&
            conn->handler == handler
        ) {
            return;
        }
    }

    Connection* newConnection = new Connection;
    newConnection->signal = signal;
    newConnection->objHandler = objHandler;
    newConnection->handler = handler;

    connections.push_back(newConnection);
};

void Base::removeConnect(
    SignalType signal,
    Base* objHandler,
    HandlerType handler
) {
    if (connections.size() != 0) {
        for (
            std::vector<Connection*>::iterator it = connections.begin();
            it != connections.end();
            ++it
        ) {
            if (
                (*it)->signal == signal &&
                (*it)->objHandler == objHandler &&
                (*it)->handler == handler
            ) {
                connections.erase(it);
            }
        }
    }
};

void Base::emitSignal(SignalType signal, std::string& action) {
    (this->*signal)(action);
    for (Connection* conn : connections) {
        if (conn->signal == signal) {
            (conn->objHandler->*(conn->handler))(action);
        }
    }
};

void Base::setNumber(int num) {
    number = num;
};

int Base::getNumber() {
    return number;
};