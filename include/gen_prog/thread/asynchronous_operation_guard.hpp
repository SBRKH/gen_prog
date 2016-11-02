#ifndef gen_prog__asynchronous_operation_guard_hpp
#define gen_prog__asynchronous_operation_guard_hpp



#include <atomic>
#include <exception>
#include <thread>
#include <stdexcept>



namespace gen_prog {
namespace thread {


class asynchronous_operation_guard
{
public:
    asynchronous_operation_guard() : _enabled(true), _running(false) {}
    asynchronous_operation_guard(bool enabled, bool running) : _enabled(enabled), _running(running) {}

    asynchronous_operation_guard(const asynchronous_operation_guard &) = delete;
    asynchronous_operation_guard(asynchronous_operation_guard &&) = delete;

    ~asynchronous_operation_guard() { if (running()) { std::terminate(); } }


    asynchronous_operation_guard & operator = (const asynchronous_operation_guard &) = delete;
    asynchronous_operation_guard & operator = (asynchronous_operation_guard &&) = delete;


    void enable() { _enabled.store(true); }
    void disable()   { _enabled.store(false); }

    bool enabled() const { return _enabled.load(); }


    void begin()
    {
        throw_if_not_enable();
        _running.store(true);
    }
    void end()   { _running.store(false); }

    bool running() const { return _running.load(); }

    template<typename Rep, typename Period>
    void wait_end(const std::chrono::duration<Rep, Period> & time)
    {
        while(running()) { std::this_thread::sleep_for(time); }
    }

private:
    void throw_if_not_enable() const { if ( ! enabled() ) { throw std::runtime_error("async operation is disable."); } }


private:
    std::atomic_bool _enabled;
    std::atomic_bool _running;
};


} // namespace thread
} // namespace gen_prog

#endif // gen_prog__asynchronous_operation_guard_hpp
