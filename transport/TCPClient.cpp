#include"TCPClient.h"

using namespace core;

TCPClient::TCPClient(const std::string& arHost, Port arPortNum):
     mSocket(streamSocket())
    ,mAddress(arHost)
    ,mPortNum(arPortNum)
{
    setSocketOptions();
}

void TCPClient::connect()
{
    struct sockaddr_in lSockAddress{};
    lSockAddress.sin_family       = AF_INET;
    lSockAddress.sin_port         = htons(mPortNum);
    lSockAddress.sin_addr.s_addr  = inet_addr(mAddress.c_str());

    if (::connect(mSocket.get(), (struct sockaddr*)&lSockAddress, sizeof(lSockAddress)) != 0)
    {
        mSocket.close();
        throw std::runtime_error("TCPClient:: failed to connect [Error:", strerror(errno) + "]" );
    }
}

size_t TCPClient::send(const char* arData, size_t arSize)
{
    return mSocket.send(arData, arSize);
}

size_t TCPClient::recv(char* arBuffer, size_t arSize)
{
    return mSocket.recv(arBuffer, arSize);
}

void TCPClient::disconnect()
{   
    //causes all or part of connection to be shut down
    //SHUT_RD: further receptions will be disallowed
    //SHUT_WR: further transmissions will be disallowed
    //SHUT_RDWR: receptions and transimissions are disallowed 
    if (::shutdown(mSocket.get(), SHUT_RDWR) != 0)
    {
        throw std::runtime_error("TCPClient::disconnect failed [Error:" + strerror(errno) + "]");
    }

    mSocket.close();
}

void TCPClient::setSocketOptions()
{
    mSocket.setSoReuseAddr();
}