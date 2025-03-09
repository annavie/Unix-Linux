#include <iostream>
#include <thread>

void mythread() {
    std::cout << "hello from thread" << std::endl;
}

int main() {
    std::thread t(mythread);

    //t.join();
   // t.join();

//    t.detach();
//    t.detach();


    return 0;
}
