//
// Created by uberslam on 2/16/18.
//

#ifndef THREADING_EXAMPLE_LOCK_GUARD_H
#define THREADING_EXAMPLE_LOCK_GUARD_H
namespace custom_lock_guard _GLIBCXX_VISIBILITY(default) {
/// Assume the calling thread has already obtained mutex ownership
/// and manage it.
    struct adopt_lock_t {
    };

/// Tag used to make a scoped lock take ownership of a locked mutex.
    constexpr adopt_lock_t adopt_lock{};


/** @brief A movable scoped lock type.
 *
 * A unique_lock controls mutex ownership within a scope. Ownership of the
 * mutex can be delayed until after construction and can be transferred
 * to another unique_lock by move construction or move assignment. If a
 * mutex lock is owned when the destructor runs ownership will be released.
 */
    template<typename _Mutex>
    class LockGuard {
    public:
        typedef _Mutex mutex_type;

        explicit LockGuard(mutex_type &__m) : _M_device(__m) { _M_device.lock(); }

        LockGuard(mutex_type &__m, adopt_lock_t) : _M_device(__m) {} // calling thread owns mutex

        ~LockGuard() { _M_device.unlock(); }

        LockGuard(const LockGuard &) = delete;

        LockGuard &operator=(const LockGuard &) = delete;

    private:
        mutex_type &_M_device;
    };

}
#endif //THREADING_EXAMPLE_LOCK_GUARD_H
