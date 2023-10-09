#ifndef SERVER_H
#define SERVER_H

#include "server/iohandler.h"

#include <string>

//  服务器配置参数类
class ServerConfig {
public:
    void SetIp(std::string ip) {
        ip_ = ip;
    }
    void SetPort(int port) {
        port_ = port;
    }
private:
    std::string ip_;
    int port_;
};

//  策略模式的环境类  建造模式的抽象产品类
class AbstractServer {
public:
    virtual void SetServerConfig(ServerConfig* server_config) = 0;
    virtual void SetIOHandler(IOEventHandler* io_handler) = 0;
    virtual void Start() = 0;
    virtual ~AbstractServer() {}
protected:
    ServerConfig* server_config_; // 服务器配置参数
    IOEventHandler* io_handler_;  // 监听io事件的方式
};

//  建造模式中的抽象建造者类
class AbstractServerBuilder {
public:
    AbstractServerBuilder() {}
    //  以下为两个抽象产品的构造过程
    virtual void BuildServerConfig(ServerConfig* server_config) = 0;
    virtual void BuildIOHandler(IOEventHandler* io_handler) = 0;
    AbstractServer* GetProduct() {
        return server_product_;
    }
    virtual ~AbstractServerBuilder(){}
protected:
    AbstractServer* server_product_; // 建造者建造的产品
};


//  建造模式中的具体产品类
class ConcreteServer : public AbstractServer {
public:
    virtual void SetServerConfig(ServerConfig* server_config) override; // 配置服务器的参数
    virtual void SetIOHandler(IOEventHandler* io_handler) override; // 配置服务器监听io的方式
    virtual void Start() override;
};

//  建造模式的具体建造者类
class ConcreteServerBuilder : public AbstractServerBuilder {
public:
    ConcreteServerBuilder(AbstractServer* server_product) {
        server_product_ = server_product;
    }
    virtual void BuildServerConfig(ServerConfig* server_config) override {
        server_product_->SetServerConfig(server_config);
    }
    virtual void BuildIOHandler(IOEventHandler* io_handler) override {
        server_product_->SetIOHandler(io_handler);
    }
};

//  指挥者类
class Director {
public:
    Director(AbstractServerBuilder* pBuilder) : pBuilder_(pBuilder) {}
    AbstractServer* CreateServer(ServerConfig* server_config, IOEventHandler* io_handler); // 指挥者创建服务器
private:
    AbstractServerBuilder* pBuilder_;
};


#endif