#pragma once
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/tcp.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

namespace core
{
    class Socket
    {
    public:
        Socket(int arFD);
        ~Socket();

        //not copyable
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;
        //Moveable
        Socket(Socket&&) = default;
        Socket& operator=(Socket&&) = default;

        int get() const noexcept { return mSockFd; }
        void close();
        explicit operator bool()const noexcept { return mSockFd != INVALID_SOCKET; }

        //allows reuse of local addresses, allows process to rebind to IP/socket combo
        void setSoReuseAddr(bool arEnabled = true) 
        { 
            int lVal(arEnabled ? 1: 0);

            setsockopt(mSockFd, SOL_SOCKET, SO_REUSEADDR, &lVal, sizeof(lVal)); 
        }

        //lingers on close() if data is present. action taken when unsent messages queue on a socket and close() is performed
        //SO_LINGER is set : system shall block the process during the close() untill it can transmit the data or timer expires
        //NOT set : closed() will go ahead
        void setSoLinger(const linger& arVal) { setsockopt(mSockFd, SOL_SOCKET, SO_LINGER, &arVal, sizeof(arVal)); }

        //SendBufferSize
        void setSoSndBuf(int arSize) { setsockopt(mSockFd,SOL_SOCKET, SO_SNDBUF, &arSize, sizeof(arSize)); }
        //Receive Buffer size
        void setSoRcvBuf(int arSize) { setsockopt(mSockFd, SOL_SOCKET, SO_RCVBUF, &arSize, sizeof(arSize)); }
        
        //NON Blocking socket
        void setNonBlock() { fcntl(mSockFd, F_SETFL, O_NONBLOCK); }

        // enable or disable receiving of SO_TIMESTAMP control message.
        //cmsg_data denotes reception time of the last packet passed to the user in this call
        void setSoTimestampNs(bool enabled = true) 
        {
            int lVal(enabled ? 1: 0);
            setsockopt(mSockFd, SOL_SOCKET, SO_TIMESTAMP, &lVal , sizeof(lVal));
        }

        //TCP optimization disables nagle algorithm
        void setTcpNoDelay(bool enabled = true) 
        {
            int lVal(enabled ? 1: 0);
            setsockopt(mSockFd, IPPROTO_TCP, TCP_NODELAY, &lVal, sizeof(lVal));
        }
        /*
        In case buffer does not fit in send buffer of socket send blocks if socket is blocking
        or fails with EAGAIN or EWOULDBLOCK in non-blocking mode
        returns number of bytes sent might be less than what you requested
        */
        size_t send(const void* arBuffer, size_t arSize, int arFlags=0);

        /*
        If no messages are available at socket the receive calls wait for a message to arrive if socket is blocking
        or returns -1 and errno set to EAGAIN and EWOULDBLOCK in case of non-blocking.
        returns data upto requested amount rather than waiting for full amount of requested data
        return 0: remote side has closed the connection
        */
        size_t recv(void* arBuffer, size_t arSize, int arFlags=0);
    private:
        static constexpr int INVALID_SOCKET{-1};
        int mSockFd;//socket file descriptor
    };

    //helper functions to create stream and datagram sockets
    inline Socket streamSocket()
    {
        //domain- communication domain AF_INET, AF_INET6
        //socket type - SOCK_STREAM: reliable connection based, SOCK_DGRAM:unreliable and connectionless, SOCK_RAW: raw network protocol access
        // protocol type - 0 : IP
        return Socket{::socket(AF_INET, SOCK_STREAM, 0)};
    }

    inline Socket datagramSocket()
    {
       return Socket{::socket(AF_INET, SOCK_DGRAM, 0)};
    }
}