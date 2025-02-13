#include <iostream>
#include <thread>
#include "module1.h"
#include "module2.h"

void execute_module1() {
    std::cout << "Thread " << std::this_thread::get_id() << " executing module1_function." << std::endl;
    module1_function();
}

void execute_module2() {
    std::cout << "Thread " << std::this_thread::get_id() << " executing module2_function." << std::endl;
    module2_function();
}

int main() {
    std::thread t1(execute_module1);
    std::thread t2(execute_module2);
    
    t1.join();
    t2.join();
    
    std::cout << "All tasks finished execution." << std::endl;
    return 0;
}
