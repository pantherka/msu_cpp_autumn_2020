#pragma once

#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>


class ThreadPool
{
    bool exists_ = false;
    std::vector<std::thread> pool_;
    std::queue<void *> tasks_;
    std::condition_variable is_ready_;
    std::mutex queue_lock_;

public:
    explicit ThreadPool(size_t poolSize): exists_(true) {
        for (size_t i = 0; i < poolSize; ++i) {
            std::thread t(&ThreadPool::process, this, i);
            pool_.push_back(std::move(t));
        }
        
    }

    void process(size_t i);

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;

    ~ThreadPool() {
        exists_ = false;
        is_ready_.notify_all();
        for (size_t i = 0; i < pool_.size(); ++i) {
            pool_[i].join();
        }
    }
};



template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    auto task = std::async(std::launch::deferred, func, args...);
    
    queue_lock_.lock();
    tasks_.push(&task);
    queue_lock_.unlock();
    is_ready_.notify_one();
    return task;
}

void ThreadPool::process(size_t i) {
    while(exists_) {
        std::unique_lock<std::mutex> lock(queue_lock_);
        if (tasks_.empty()) {
            is_ready_.wait(lock);
        }
        
        if (tasks_.empty()) {
            continue;
        }
        auto task = (std::future<void>*)tasks_.front();
        tasks_.pop();
        lock.unlock();
        (*task).wait();
    }
}