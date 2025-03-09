#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

std::atomic<int> counter{0};

void incrementCounter() {
    counter++;
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter);
    }

    for (auto &t : threads) {
        t.join();
       //t.detach();
    }

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}
