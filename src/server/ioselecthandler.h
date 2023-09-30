#ifndef IOSELECTHANDLER_H
#define IOSELECTHANDLER_H

#include "server/iohandler.h"

//  具体产品类 / 具体策略类
class IOSelectHandler : public IOEventHandler {
public:
    virtual void HandleEvent() override;
};

//  具体工厂类
class IOSelectFactory : public IOFactoryHandler {
public:
    virtual IOEventHandler* Create() override {
        return new IOSelectHandler();
    }
};

#endif