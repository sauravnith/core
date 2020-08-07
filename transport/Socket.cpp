#include"Socket.h"
#include<string.h>
#include<stdexcept>

using namespace core;

Socket::Socket(int arFd): mSockFd(arFd)
{
    if(mSockFd == INVALID_SOCKET)
    {
        throw std::runtime_error("Socket:: Invalid socket file descriptor");
    }
    
}

Socket::~Socket()
{
    close();
}

size_t Socket::send(const void* arBuffer, size_t arSize, int arFlags)
{
    const auto lSentBytes = ::send(mSockFd,arBuffer, arSize, arFlags);
    if(lSentBytes < 0)
    {
         throw std::runtime_error("Socket:: Failed to send data [Error:" + std::string(strerror(errno)) + "]");
    }

    return lSentBytes;
}

size_t Socket::recv(void* arBuffer, size_t arSize, int arFlags)
{
    const auto lRecv = ::recv(mSockFd, arBuffer, arSize,arFlags);

    if(lRecv < 0 && errno != EWOULDBLOCK)
    {
        throw std::runtime_error("Socket: recv failed socket disconnected [Error:"+ std::string(strerror(errno)) + "]");
    }
    //returning zero means remote side has closed connection
    return lRecv;
}

void Socket::close()
{
    if(mSockFd == INVALID_SOCKET) return;
    auto lError = ::close(mSockFd);

    switch(lError)
    {
        case EBADF:
            throw std::runtime_error("Socket:: close failed as FD is not valid file descriptor");
            break;
        case EINTR:
            throw std::runtime_error("Socket:: close failed as call was interrupted by a signal");
            break;
        case EIO:
            throw std::runtime_error("Socket:: close failed as I/O error occurred");
            break;
    }

    mSockFd = INVALID_SOCKET;
}
