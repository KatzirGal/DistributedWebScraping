#include "WorkerCore.h"

#include <boost/asio/signal_set.hpp>

int main(int argc, char* argv[])
{
    net::io_context ioc;

    unsigned short port = 8000;
    WorkerCore server(ioc, port);
    server.start();

    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto) {
        ioc.stop();
        });

    ioc.run();

    return 0;
}
