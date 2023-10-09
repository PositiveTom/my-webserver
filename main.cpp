#include <iostream>
#include <vector>
#include "server/server.h"
#include "server/ioselecthandler.h"
#include "threadpool/threadpool.h"
#include "memorypool/memorypool.h"

int main() {

    //  1. 创建具体的服务器类
    AbstractServer* server = new ConcreteServer();
    //      1.1 创建具体的服务器建造类
    AbstractServerBuilder* server_builder = new ConcreteServerBuilder(server);

    //  2. 创建监听事件的具体工厂实例
    IOFactoryHandler* io_factory_handler = new IOSelectFactory();
    //      2.1 创建对于的具体io事件
    IOEventHandler* io_handler = io_factory_handler->Create();

    //  3. 创建服务器配置参数类
    ServerConfig* server_config = new ServerConfig();
    //      3.1 传递参数---待定

    //  4. 创建指挥者
    Director* director = new Director(server_builder);
    AbstractServer* server_product = director->CreateServer(server_config, io_handler);

    //  实际上, server_product_ 与 server 相同！！！
    // ThreadPool threadpool;
    // threadpool.enque([](){
    //     std::cout << "hello" << std::endl;
    // });
    std::vector<int, MemoryPool<int>> aa;

    delete director;
    delete server_config;
    delete io_handler;
    delete io_factory_handler;
    delete server_builder;
    delete server;

    return 0;
}