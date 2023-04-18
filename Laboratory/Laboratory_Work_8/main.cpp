#include <iostream>
#include "Stack.h"

int main() {
    Stack<int> stack(3);
    std::cout << "Size: " << stack.Size() << std::endl;
    stack.Push(0);
    stack.Push(1);
    stack.Push(2);
    try {
        stack.Push(3);
    }
    catch(const std::overflow_error& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
    std::cout << "Top: " << stack.Top() << std::endl;
    stack.Pop();
    std::cout << "Size: " << stack.Size() << std::endl;
    std::cout <<"Top: " << stack.Top() << std::endl;
    return 0;
}
