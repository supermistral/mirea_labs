#ifndef _BASE_H
#define _BASE_H
#include <vector>
#include <string>


class Base;

typedef void (Base::*SignalType)(std::string&);
typedef void (Base::*HandlerType)(std::string);


class Base {

#define SIGNAL(cl, f) ((SignalType)(&cl::f))
#define HANDLER(cl, f) ((HandlerType)(&cl::f))

public:
    Base(Base*, std::string);
    ~Base();

    void setName(std::string);
    std::string getName();
    void printTree();
    void setParent(Base*);
    Base* getParent();

    Base* getObject(std::string);

    void printReadyTree();
    void setReady(int);
    int getReady();

    void printModelTree(int);

    Base* getObjectByCoord(std::string);

    int getNumber();
    void setNumber(int);
    void setConnect(SignalType, Base*, HandlerType);
    void removeConnect(SignalType, Base*, HandlerType);
    void emitSignal(SignalType, std::string&);

private:
    std::string name;
    Base* parent;
    std::vector<Base*> listChildren;
    int ready;

    struct Connection {
        SignalType signal;
        HandlerType handler;
        Base* objHandler;
    };

    std::vector<Connection*> connections;
    int number;
};

#endif