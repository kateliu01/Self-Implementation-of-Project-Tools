
/*
    实现线程池：
        创建线程池
        创建线程
        绑定线程
        添加任务队列
        释放线程
        销毁线程池
*/
#include<vector>
#include<thread>
#include<queue>
#include<functional>
#include<mutex>
#include<chrono>
#include<iostream>
#include<condition_variable>
std::mutex mt;
std::condition_variable cv;
class ThreadPool{
public:
    // 构造函数
    ThreadPool(){}
    ThreadPool(int thread_num):_stopPool(false){
        // 创建线程
        for(int i=0; i<thread_num; i++) {
            // 这里居然不用构造std::thread！
            _threads.emplace_back([this]{
                while(true) {
                    std::function<void()> oneTask;
                    {
                        std::unique_lock<std::mutex> lock(mt);
                        cv.wait(lock, [this]{return this->_stopPool || !this->_taskQueue.empty();});
                        // if (this->_stopPool) return; //  线程池要停止 && 任务队列为空
                        if (this->_stopPool && this->_taskQueue.empty()) return;
                        oneTask = std::move(this->_taskQueue.front());
                        this->_taskQueue.pop();
                    }
                    oneTask();
                }
            });
        }
    }
    // 析构函数
    ~ThreadPool(){
        // _stopPool 可以锁一下
        _stopPool=true;
        // 这要通知所有线程吖
        cv.notify_all();
        for(auto& t: _threads) t.join();
    }
    // 添加任务队列
    template<class F, class... ARGS>
    void addTask(F&& f, ARGS&&...args) {
        {
            std::unique_lock<std::mutex> lock(mt);
            auto b = std::bind(std::forward<F>(f), std::forward<ARGS>(args)...);
            // _taskQueue.emplace([=]{b();});
            _taskQueue.emplace(b); 
        }
        cv.notify_one();
        // cv.notify_all();
    }
private:
    bool _stopPool;
    std::vector<std::thread> _threads;
    std::queue<std::function<void()>> _taskQueue;
};
void fun1(int a, int b, int c) {
    c = a+b;
    std::cout << c << " ";
}
void fun2(int a, int b, int c) {
    c = a-b;
    std::cout << c << " ";
}
void fun3(int a, int b, int c) {
    c = a*b;
    std::cout << c << " ";
}
int main() {
    const int num = 3;
    int a=10, b=5, c=0;
    // 暂时只有这一种构造方法
    ThreadPool pool(num);
    pool.addTask(fun1, a, b, c);
    pool.addTask(fun2, a, b, c);
    pool.addTask(fun3, a, b, c);
    pool.addTask(fun1, a, b, c);
    pool.addTask(fun2, a, b, c);
    pool.addTask(fun3, a, b, c);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
