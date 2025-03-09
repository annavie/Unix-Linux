#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void waitingThread() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []() { return ready; });
    std::cout << "Waiting thread: Condition met, proceeding." << std::endl;
}

void signalingThread() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Signaling thread: Condition is now true." << std::endl;
    }
    cv.notify_one();
}

int main() {
    std::thread t1(waitingThread);
    std::thread t2(signalingThread);
    
    t1.join();
    t2.join();
    
    return 0;
}
