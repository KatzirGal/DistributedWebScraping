#include "WorkerCore.h"

int main(int argc, char* argv[])
{
    net::io_context ioc;
    WorkerCore workerCore(ioc, 8000);
    workerCore.start();
    return 0;
}