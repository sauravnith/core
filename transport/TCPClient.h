#pragma once
#include"Socket.h"
#include <utils/Types.h>
#include <string.h>

namespace core
{
    class TCPClient
    {
    public:
        TCPClient(const std::string& arHost, Port arPortNum);
        void connect();
        void disconnect();
        size_t send(const char* arData, size_t arSize);
        size_t recv(char* arBuffer, size_t arSize);
    private:
        Socket mSocket;
        std::string mAddress;
        Port mPortNum;

        void setSocketOptions();
    };
}