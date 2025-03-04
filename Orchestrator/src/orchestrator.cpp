#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>

std::string masterCommand = "./master_node/bin/master";
std::string workerCommand = "./worker_node/bin/worker";
int workerCount = 3; // Change this to increase/decrease workers

std::vector<int> workerPIDs;

void startMaster() {
    int result = std::system(masterCommand.c_str());
    if (result != 0) {
        std::cerr << "Failed to start Master Node!" << std::endl;
    }
}

void startWorkers() {
    for (int i = 0; i < workerCount; ++i) {
        int result = std::system(workerCommand.c_str());
        if (result != 0) {
            std::cerr << "Failed to start Worker " << i + 1 << "!" << std::endl;
        }
    }
}

int main() {
    std::cout << "[Orchestrator] Starting Master Node..." << std::endl;
    std::thread masterThread(startMaster);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "[Orchestrator] Starting " << workerCount << " Worker Nodes..." << std::endl;
    std::thread workerThread(startWorkers);

    masterThread.join();
    workerThread.join();

    std::cout << "[Orchestrator] All processes started!" << std::endl;
    return 0;
}
