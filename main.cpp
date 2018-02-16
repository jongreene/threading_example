#include <iostream>
#include <thread>
#include <mutex>
#include "LockGuard.h"

static const int num_threads = 10;
static std::mutex barrier;
using namespace custom_lock_guard;

//This function will be called from a thread
void call_from_thread(int threadNumber) {
    // blocks all other code execution until current thread is finished
    LockGuard<std::mutex> block_threads_until_finish_this_job(barrier);

    std::cout << "Thread: " << threadNumber << std::endl;
}

int main() {
    std::thread t[num_threads];

    //Launch a group of threads
    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(call_from_thread, i);
    }

    std::cout << "Launched from the main\n";

    //Join the threads with the main thread
    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }

    std::cout << "All threads finished\n";

return 0;
}