#include "WorkerCore.h"

int main(int argc, char* argv[])
{
    net::io_context ioc;
    WorkerCore workerCore(ioc, 8000);
    return 0;
    //return workerCore.run(argc, argv);
}