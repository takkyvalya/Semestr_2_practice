#include <iostream>
#include <iostream>
#include <typeinfo>
#include <cstring>
#include <vector>

struct String
{
private:
    size_t m_size;
    char* m_str = nullptr;
    friend std::ostream& operator<<(std::ostream& out, String& s);
    friend std::istream& operator>>(std::istream& in, String& s);

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

    ~String() {
        std::cout << "Destructor "<< m_str << std::endl;
        if(m_str != nullptr)
            delete[] m_str;
    }

    String& operator=(String temp)
    {
        // Идиома Copy-and-swap
        std::cout << "Copy assigment operator" << std::endl;
        std::swap(m_size, temp.m_size);
        std::swap(m_str, temp.m_str);
        return *this;
    }

    String operator+(const String& temp)
    {
        std::cout << "Sub assigment operator" << std::endl;
        String result(m_size + temp.m_size + 1);
        for(int i =0; i < result.m_size;i++){
            if(i < m_size){
                result.m_str[i]  = *&m_str[i];
            }
            else{
                result.m_str[i]  = *&temp.m_str[i-m_size];
            }
        }
        result.m_str[result.m_size] = 0;
        return result;
    }

    String& operator+=(const String& temp) {
        std::cout << "Sub= assigment operator" << std::endl;
        size_t param = m_size;
        m_size = m_size + temp.m_size + 1;
        for(int i =param; i < m_size;i++){
            m_str[i] = *(&(temp.m_str[i - param]));
        }
        m_str[m_size] = 0;

        return *this;
    }

    char& operator [] (size_t i) {
            std::cout << "Change assigment operator"<< std::endl;
        return *(m_str + i);
    }

    bool operator<(String temp){
        std::cout << "Comparison#1 operator" << std::endl;
        return (this->m_size < temp.m_size);
    }

    bool operator>(String temp){
        std::cout << "Comparison#2 operator" << std::endl;
        return (this->m_size > temp.m_size);
    }

    bool operator==(String temp){
        std::cout << "Equality operator" << std::endl;
        if(operator<(temp) == 1 || operator>(temp) == 1)
            return false;
        else{
            bool flag = true;
            for(int i =0; i< m_size;i++){
                if(m_str[i] != temp.m_str[i]) {
                    flag = false;
                    break;
                }
            }
            return flag;
        }
    }

    int find(char c){
        for(int i =0; i<m_size;i++){
            if(m_str[i] == c)
                return i;
        }
        return -1;
    }

    char& at (size_t i) {
        std::cout << "At operator"<< std::endl;
        if(i<m_size && i >=0)
            return *(m_str + i);
        else{
            std::cout << "Error";
        }
    }

    void Print() const
    {
        for (int i = 0; i < m_size; i++)
            std::cout << m_str[i];
        std::cout<<std::endl;
    }

    size_t length() const	{ return m_size; } // Константный метод
    char* c_str() { return m_str; }
};

std::ostream& operator<<(std::ostream& out, String& s) {
    for (int i = 0; i < s.m_size; i++)
        out << s.m_str[i];
    out << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, String& s){
    char c;
    while(in.get(c)) {
        if (c == '\n' || c == ' ')
            break;
        char* str = new char[s.m_size + 1];

        for (int i = 0; i < s.m_size; i++)
            str[i] = s.m_str[i];

        str[s.m_size] = c;

        delete[] s.m_str;
        s.m_str = str;
        delete[] str;
        s.m_size++;
    }
    return in;
}


int main()
{
    String s1("Hello, world! ");
    String s2("test");
    String s3("Hello");

    s3.at(3)='5';
    std::cin >> s3;
    std::cout << s3;

    return 0;
}


