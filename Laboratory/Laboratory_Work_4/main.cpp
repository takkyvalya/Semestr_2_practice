#include <iostream>

template<typename T, int N, int M>
class Matrix
{
private:
    T m_matrix[N][M];
    friend std::ostream& operator<<(std::ostream& out, Matrix& matrix);
    friend std::istream& operator>>(std::istream& in, Matrix& matrix);
public:
    //Базовый конструктор
    Matrix(){}

    //Конструктор копирования
    Matrix(const Matrix& other)
    {
        std::cout << "Copy Constructor" << std::endl;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                m_matrix[i][j] = other.m_matrix[i][j];
    }

    Matrix& operator=(Matrix temp)
    {
        // Идиома Copy-and-swap
        std::cout << "Copy assigment operator" << std::endl;
        return *this;
    }

    Matrix& operator+(Matrix temp){
        Matrix result(this);

    }

    double determinant()
    {
        //if (N == 2 && M == 2)
        //{

        //}
        //else if (N == 3 && M == 3)
        //{
        //    m_matrix[2][2];
        //}
    }
    friend std::ostream& operator<<(std::ostream& out, Matrix& m) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++)
                out << m.m_matrix[i][j] << " ";
            out << std::endl;
        }
        return out;
    }
/*
    friend std::istream& operator>>(std::istream& in, Matrix& m){
        for (int i = 0; i < m.N; i++)
            for (int j = 0; j < m.M; j++)
                in >> m.m_matrix[i][j];
        return in;
    }
    */
};

using Matrix22i = Matrix<int, 2, 2>; // typedef
using Vector2i = Matrix<int, 2, 1>;

int main(){

    Matrix22i M1;

    std::cout << M1;

    Matrix22i M2;

}