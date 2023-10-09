#include "threadpool/threadpool.h"

ThreadPool::ThreadPool() {
    stop_ = false;
    
    size_t cpu_nums = std::thread::hardware_concurrency();

    // cpu_nums = worker_nums == -1 ? worker_nums : cpu_nums;

    for(int i=0; i<cpu_nums; i++) {
        workers_.emplace_back([this](){
            for(;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->mutex_);
                    this->cond_.wait(lock, [this](){
                        return this->stop_ || !this->tasks_.empty();
                    });

                    if( this->stop_ && this->tasks_.empty()) {
                        return;
                    }

                    task = std::move(this->tasks_.front());
                    this->tasks_.pop();
                }
                task();
            }
        });
    }   
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        stop_ = true;
    }
    cond_.notify_all();
    for(auto& worker : workers_) {
        worker.join();
    }
}