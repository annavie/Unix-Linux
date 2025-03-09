#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

// void mythread(int threadID) {
//     std::cout << "hello from mythread" << std::endl;
//     {
//         std::lock_guard<std::mutex> lock(mtx);
//         counter++;
//         std::cout << "Thread " << threadID << " incremented counter to " << counter << std::endl;
//     }
// }

void mythread(int threadID) {
    std::cout << "hello from mythread" << std::endl;
    
    mtx.lock();
    
    counter++;
    std::cout << "Thread " << threadID << " incremented counter to " << counter << std::endl;
    
    mtx.unlock();
}

int main() {
    std::thread t0(mythread, 0);
    std::thread t1(mythread, 1);

    t0.join();
    t1.join();
    
    return 0;
}
