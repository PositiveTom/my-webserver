#include "server/server.h"

void ConcreteServer::SetServerConfig(ServerConfig* server_config) {
    server_config_  = server_config;
}

void ConcreteServer::SetIOHandler(IOEventHandler* io_handler) {
    io_handler_ = io_handler;
}

void ConcreteServer::Start() {
    
}

AbstractServer* Director::CreateServer(ServerConfig* server_config, IOEventHandler* io_handler){
    pBuilder_->BuildServerConfig(server_config);
    pBuilder_->BuildIOHandler(io_handler);
    return pBuilder_->GetProduct();
}