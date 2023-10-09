#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>
//  工作线程 任务缓冲队列 添加任务的接口

class ThreadPool {
public:
    ThreadPool();

    template<class Functor, class... Args>
    std::future<typename std::result_of<Functor(Args...)>::type> enque(Functor&& F, Args&&... args) {
        using return_type = typename std::result_of<Functor(Args...)>::type;

        std::shared_ptr<std::packaged_task<return_type()>> pack_task_ptr = 
            std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Functor>(F), std::forward<Args>(args)...));

        std::future<return_type> return_ret = pack_task_ptr->get_future();
        {
            std::unique_lock<std::mutex> lock(mutex_);

            if(stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks_.emplace([pack_task_ptr](){
                (*pack_task_ptr)();
            });
        }   
        cond_.notify_one();
        return return_ret;     
    }

    ~ThreadPool();

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::condition_variable cond_;
    std::mutex mutex_;
    bool stop_;
};


#endif