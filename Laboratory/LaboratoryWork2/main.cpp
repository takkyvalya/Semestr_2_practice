#include <iostream>
#include <iostream>
#include <typeinfo>
#include <cstring>

struct String
{
private:
    size_t m_size;
    char* m_str = nullptr;

public:
    String(size_t size) : m_size(size), m_str(new char[size+1])
    {
        std::cout << "Constructor #1" << std::endl;
        //std::fill(m_str, m_str + m_size, c); // memset
        m_str[m_size] = 0;
    }


    // Member initializer list (список инициализации членов класса)
    String(char* str) : m_size(strlen(str)), m_str(new char[m_size+1])
    {
        std::cout << "Constructor #2" << std::endl;
        std::copy(str, str+m_size, m_str); // memcpy
        m_str[m_size] = 0;
    }

    // Конструктор копирования + делегирующий конструктор
    String(const String& other) : String(other.m_str)
    {
        std::cout << "Copy Constructor" << std::endl;
    }

    String& operator=(String temp)
    {
        // Идиома Copy-and-swap
        std::cout << "Copy assigment operator" << std::endl;
        std::swap(m_size, temp.m_size);
        std::swap(m_str, temp.m_str);
        return *this;
    }

    String& operator+(const String& temp)
    {
        std::cout << "Sub assigment operator" << std::endl;
        String result(m_size + temp.m_size + 1);
        for(int i =0; i < result.m_size;i++){
            if(i < m_size){
                result.m_str[i]  = *&m_str[i];
            }
            else{
                result.m_str[i]  = *&temp.m_str[i-temp.m_size-1];
            }
        }
        result.m_str[result.m_size] = 0;

        std::cout << "Type "<< typeid(this).name()  << " "  << typeid(result).name()<< std::endl;
        return result;
    }

    String& operator+=(const String& temp) {
        size_t param = m_size;
        m_size = m_size + temp.m_size + 1;
        for(int i =param; i < m_size;i++){
            m_str[i] = *(&(temp.m_str[i - param]));
        }
        m_str[m_size] = 0;

        return *this;
    }

    ~String() {
        std::cout << "Destructor " << m_str << std::endl;
        if(m_str != nullptr)
            delete[] m_str;
    }

    size_t Size() const		// Константный метод
    {
        return m_size;
    }

    void Print() const
    {
        for (int i = 0; i < m_size; i++)
            std::cout << m_str[i];
        std::cout<<std::endl;
    }
};

void f(String s)
{
    s.Print();
}

int main()
{
    String s1("Hello, world!");
    String s2("test ");
    String s3("111");

    s3 = s2 + s1;
    //(s2+s1)->Print();
//    s3 += s2;

    s1.Print();
    s2.Print();
    s3.Print();

    return 0;
}


