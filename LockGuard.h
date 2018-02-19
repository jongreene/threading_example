//
// Created by uberslam on 2/16/18.
//

#ifndef THREADING_EXAMPLE_LOCK_GUARD_H
#define THREADING_EXAMPLE_LOCK_GUARD_H
namespace custom_lock_guard _GLIBCXX_VISIBILITY(default) {
    template<typename _Mutex>
    class LockGuard {
    public:
        LockGuard(std::mutex &_M_device) : _M_device(_M_device) {
            _M_device.lock();
            std::cout << std::endl << "\tThread locked!" << std::endl;
        }
        // calling thread owns mutex

        ~LockGuard() {
            _M_device.unlock();
            std::cout << std::endl << "\tThread unlocked!" << std::endl;
        }

    private:
        std::mutex &_M_device;
    };

}
#endif //THREADING_EXAMPLE_LOCK_GUARD_H
