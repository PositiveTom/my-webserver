#ifndef IOHANDLER_H
#define IOHANDLER_H

//  抽象产品类 / 抽象策略类
class IOEventHandler {
public:
    virtual void HandleEvent() = 0; // 策略模式公共算法接口
    virtual ~IOEventHandler() {}
};

//  抽象工厂类
class IOFactoryHandler {
public:
    virtual IOEventHandler* Create() = 0;
    virtual ~IOFactoryHandler() {}
};

#endif