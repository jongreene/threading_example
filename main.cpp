#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include "LockGuard.h"

static const int num_threads = 10;
static std::mutex barrier;
using namespace custom_lock_guard;

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> dis(0, 6);


//This function will be called from a thread
void call_from_thread(int threadNumber) {
    // blocks all other code execution until current thread is finished
    LockGuard<std::mutex> block_threads_until_finish_this_job(barrier);

    // for simplicity a random number is generated for both seconds and nanoseconds
    std::chrono::seconds sec(dis(gen));
    std::chrono::nanoseconds nan(dis(gen));

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