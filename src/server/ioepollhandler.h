#ifndef IOEPOLLHANDLER_H
#define IOEPOLLHANDLER_H

#include "server/iohandler.h"

//  具体产品类
class IOEpollHandler : public IOEventHandler {
public:
    virtual void HandleEvent() override {}
};

//  具体工厂类
class IOEpollFactory : public IOFactoryHandler {
public:
    virtual IOEventHandler* Create() override {
        return new IOEpollHandler;
    }
};

#endif