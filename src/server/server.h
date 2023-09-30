#ifndef SERVER_H
#define SERVER_H

#include "server/iohandler.h"

//  策略模式的环境类
class Server {
public:
    Server(IOFactoryHandler* factory);
    void Start();
    ~Server();
private:
    IOEventHandler* io_handler_;
};


#endif