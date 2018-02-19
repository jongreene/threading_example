#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <condition_variable>
#include "LockGuard.h"

static const int num_threads = 3;
static std::mutex barrier;
using namespace custom_lock_guard;

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1,5);


//This function will be called from a thread
void call_from_thread(int threadNumber) {
    // blocks all other code execution until current thread is finished
    LockGuard block_threads_until_finish_this_job(barrier);

    // for simplicity a random number is generated for both seconds and nanoseconds
    std::chrono::seconds sec(distribution(generator));
    std::chrono::nanoseconds nan(0);

    std::this_thread::__sleep_for(sec,nan);
    std::cout << "Thread: " << threadNumber << " slept for " << sec.count() << " seconds and " << nan.count() << " nanoseconds." << std::endl;
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