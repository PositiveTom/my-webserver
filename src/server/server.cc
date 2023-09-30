#include "server/server.h"

Server::Server(IOFactoryHandler* factory) {
    io_handler_ = factory->Create();
}

void Server::Start() {
    io_handler_->HandleEvent(); 
}

Server::~Server() {
    delete io_handler_;
}