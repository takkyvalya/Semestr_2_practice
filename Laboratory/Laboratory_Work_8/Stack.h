//
// Created by vtakk on 18.04.2023.
//
/*
1. Невозможно выделить необходимый участок памяти под стек (std::bad_alloc).
2. Невозможно добавить новый элемент в стек (например, std::overflow_error)
3. Невозможно извлечь элемент из стека, так как стек пустой (например, std::out_of_range)
4. Невозможно посмотреть элемент на вершине стека, так как стек пустой (например, std::logic_error).
*/

template <typename T>
class Stack{
private:
    size_t s_size;
    T* s_massive;
    int top;
public:
    Stack(size_t size): s_size(size){
        try{
           s_massive = new T[s_size];
           top = -1;
        }
        catch (std::bad_alloc& e){
            std::cout << "Error in Constructor: " << e.what() << std::endl;
        }
        std::cout << "Constructor" << std::endl;
    }
    ~Stack(){
        if(s_massive != nullptr)
            delete [] s_massive;
        std::cout << "Destructor" << std::endl;
    }

    size_t Size(){
        return s_size;
    }

    bool isEmpty(){
        if(top == -1){
            return true;
        }
        return false;
    }

    bool isFull(){
        if(top == s_size - 1){
            return true;
        }
        return false;
    }

    void Push(T element){
        if(top+1 < s_size) {
            top++;
            s_massive[top] = element;
        }
        else {
            throw std::overflow_error("Overflow in Push");
        }
    }

    void Pop(){
        if(isEmpty() != true)
            top--;
        else{
            throw std::out_of_range("in Pop");
        }
    }

    T Top(){
        if(isEmpty() != true)
            return s_massive[top];
        else
            throw std::logic_error("in Top");
    }
};