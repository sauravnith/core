#include "TCPServer.h"
#include<string.h>

using namespace core;

TCPServer::TCPServer(Port arPortNum, int arMaxConnectionBackLog): 
    mSocket(streamSocket())
   ,mPortNum(arPortNum)
   ,mConnectionBackLog(arMaxConnectionBackLog) 
{
    initSocket();
}
void TCPServer::start()
{
    if (::listen(mSocket.get(), mConnectionBackLog) != 0)
    {
        close();
        throw std::runtime_error("TCPServer::start failed to start Server [Error: " + std::string(strerror(errno))+ " ]");
    }
}
void TCPServer::close()
{
    mSocket.close();
}

Socket TCPServer::accept()
{
    if(!mSocket) throw std::runtime_error("TCPServer:: failed to accept connections as socket is invalid");

    struct  sockaddr_storage    lSockAddr;
    socklen_t   lAddrSize{sizeof(lSockAddr)};

    Socket lNewSocket(::accept(mSocket.get(), (struct sockaddr*)&lSockAddr, &lAddrSize));

    if (!lNewSocket)   throw std::runtime_error("TCPServer:: failed to accept [Error:" + std::string(strerror(errno))+ "]");
    
    return lNewSocket;
}

void TCPServer::initSocket()
{
    struct sockaddr_in lSockAddr;
    bzero((char*)&lSockAddr, sizeof(lSockAddr));
    lSockAddr.sin_family       = AF_INET;
    lSockAddr.sin_port         = htons(mPortNum);
    lSockAddr.sin_addr.s_addr  = INADDR_ANY;

    if (::bind(mSocket.get(), (struct sockaddr *) &lSockAddr, sizeof(lSockAddr)) != 0)
    {
        close();
        throw std::runtime_error("TCPServer::initSocket failed to bind [Error:" + std::string(strerror(errno)) + "]");
    }

    mSocket.setSoReuseAddr(true);
}