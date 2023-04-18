#include <iostream>
#include "Stack.h"

int main() {
    Stack<int> stack(1);
    std::cout << "Size: " << stack.Size() << std::endl;
    try {
        stack.Push(5);
    }
    catch(const std::overflow_error& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
    std::cout << "Top: " << stack.Top() << std::endl;
    try {
        stack.Pop();
    }
    catch(const std::out_of_range& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
    std::cout << "Size: " << stack.Size() << std::endl;
    try {
        std::cout << stack.Top() << std::endl;
    }
    catch (const std::logic_error& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
