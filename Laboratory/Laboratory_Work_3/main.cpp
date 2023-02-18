#include <iostream>

class Complex{
private:
    double m_a;
    double m_b;
    friend std::ostream& operator<<(std::ostream& out, Complex& z);
    friend std::istream& operator>>(std::istream& in, Complex& z);
public:
    Complex(double a, double b):m_a(a), m_b(b)
    {
        std::cout << "Basic constructor"<< std::endl;
    }

    Complex (const Complex& z)
    {
        std::cout << "Cope constructor" << std::endl;
        m_a = z.m_a;
        m_b = z.m_b;
    }

    ~Complex()
    {
        std::cout << "Destructor "<< std::endl;
    }

    Complex& operator=(Complex& z)
    {
        std::cout << "Copy assigment operator" << std::endl;
        std::swap(m_a, z.m_a);
        std::swap(m_b, z.m_b);
        return *this;
    }

    Complex operator+ (Complex& z)
    {
        std::cout << "operator + " << std::endl;
        double a = m_a + z.m_a;
        double b = m_b + z.m_b;
        Complex new_z(a,b);
        return new_z;
    }

    Complex& operator+= (Complex& z)
    {
        m_a += z.m_a;
        m_b += z.m_b;
        return *this;
    }

    Complex operator* (Complex& z) const
    {
        std::cout << "operator * " << std::endl;
        double a = m_a * z.m_a - m_b * z.m_b;
        double b = m_a * z.m_b + m_b * z.m_a;
        Complex new_z(a,b);
        return new_z;
    }

    Complex& operator*= (Complex& z)
    {
        double a = m_a * z.m_a - m_b * z.m_b;
        double b = m_a * z.m_b + m_b * z.m_a;
        m_a = a; m_b = b;
        return *this;
    }

    Complex& operator++()
    {
        m_a++;
        return *this;
    }

    Complex operator++(int)
    {
        Complex copy = *this;
        m_a++;
        return copy;
    }
};

std::ostream& operator<<(std::ostream& out, Complex& z) {
    out << z.m_a << "+" << z.m_b << "i" << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Complex& z){
    double a, b;
    in >> a >> b;
    z.m_a = a;
    z.m_b = b;
    return in;
}

int main() {
    Complex z1(1,1);

    Complex z(0,0);

    std::cin >> z;
    std::cout << z;

}
