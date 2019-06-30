#include <transport/TCPServer.h>

using namespace core;

int main()
{
    Port lListenPort{3130};
    TCPServer lServer{lListenPort};
    lServer.start();

    auto lCount{2};

    while(lCount)
    {
        auto lSocket = lServer.accept();

        lSocket.send("Hello\n", 6);

        lSocket.close();
        --lCount;
    }

    return 0;
}
