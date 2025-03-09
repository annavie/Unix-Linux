#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void worker(std::promise<int> prom) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    int result = 42;
    prom.set_value(result);
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread t(worker, std::move(prom));
    int value = fut.get();
    std::cout << "Result from worker thread: " << value << std::endl;
    t.join();
    
    return 0;
}
