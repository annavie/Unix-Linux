#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx1;
std::mutex mtx2;

void threadFunc1() {
    std::cout << "Thread 1: Locking mtx1\n";
    mtx1.lock();
   // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::cout << "Thread 1: Waiting to lock mtx2\n";
    mtx2.lock(); 
    
    std::cout << "Thread 1: Acquired both locks\n";
    mtx2.unlock();
    mtx1.unlock();
}

void threadFunc2() {
    std::cout << "Thread 2: Locking mtx2\n";
    mtx2.lock();
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::cout << "Thread 2: Waiting to lock mtx1\n";
    mtx1.lock(); 
    
    std::cout << "Thread 2: Acquired both locks\n";
    mtx1.unlock();
    mtx2.unlock();
}

int main() {
    std::thread t1(threadFunc1);
    std::thread t2(threadFunc2);

    t1.join();
    t2.join();

    return 0;
}
