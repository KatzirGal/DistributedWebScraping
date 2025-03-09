#include "worker_core.h"

int main(int argc, char* argv[])
{
    WorkerCore workerCore;
    return workerCore.run(argc, argv);
}