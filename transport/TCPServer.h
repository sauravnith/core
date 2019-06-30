#pragma once
#include "Socket.h"
#include <utils/Types.h>

namespace core
{
    class TCPServer
    {
    public:
        TCPServer(Port arPortNum,int arMaxConnectionBackLog = 5);
        void start();
        void close();
        Socket accept();
    private:
        Socket mSocket;
        Port mPortNum;
        int mConnectionBackLog;

        void initSocket();
    };
}