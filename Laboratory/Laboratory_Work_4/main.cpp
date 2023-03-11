#include <iostream>
#include <cmath>

template<typename I, int P, int Q>
struct TotMas
{
    I mas[P][Q];
};

template<typename T, int N, int M>
class Matrix
{
private:
    int m_n;
    int m_m;
    T** m_matrix;
    friend std::ostream& operator<<(std::ostream& out, Matrix& matrix);
    friend std::istream& operator>>(std::istream& in, Matrix& matrix);

    void del(){
        for(int i=0;i<m_n;i++)
            delete [] m_matrix[i];

        delete [] m_matrix;
    }
public:
    //Базовый конструктор
    Matrix(){
        m_n = N;
        m_m = M;
        m_matrix = new T*[m_n];

        for(int i=0;i<m_n;i++)
            m_matrix[i] = new T[m_m];

        for (int i = 0; i < m_n; i++)
            for (int j = 0; j < m_m; j++)
                m_matrix[i][j] =0;
    }

    Matrix(int n, int m){
        m_n =n;
        m_m =m;

        m_matrix = new T*[m_n];

        for(int i=0;i<m_n;i++)
            m_matrix[i] = new T[m_m];

        for (int i = 0; i < m_n; i++)
            for (int j = 0; j < m_m; j++)
                m_matrix[i][j] =0;
    }

    //Конструктор копирования
    Matrix(const Matrix& other)
    {
        std::cout << "Copy Constructor" << std::endl;
        m_n =other.m_n;
        m_m =other.m_m;

        m_matrix = new T*[m_n];

        for(int i=0;i<m_n;i++)
            m_matrix[i] = new T[m_m];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                m_matrix[i][j] = other.m_matrix[i][j];
    }

    ~Matrix() {
        del();
    }

    Matrix& operator=(Matrix& temp)
    {
        // Идиома Copy-and-swap
        std::cout << "Copy assigment operator" << std::endl;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                m_matrix[i][j] = temp.m_matrix[i][j];
        return *this;
    }

    Matrix operator+(Matrix& temp){
        Matrix result(*this);
        for (int i = 0; i < m_n; i++)
            for (int j = 0; j < m_m; j++)
                result.m_matrix[i][j] += temp.m_matrix[i][j];
        return result;
    }

    Matrix& operator+=(Matrix& temp){
        for (int i = 0; i < m_n; i++)
            for (int j = 0; j < m_m; j++)
                m_matrix[i][j] += temp.m_matrix[i][j];
        return *this;
    }

    template<typename I, int P,int Q>
    Matrix operator*(Matrix<I,P,Q> temp){
        if(M == P) {
            std::cout << "Sub Work" << std::endl;
            Matrix result(N, Q);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < Q; j++)
                    for (int k = 0; k < M; k++) {
                        result.m_matrix[i][j] += m_matrix[i][k] * temp.GetEl(k, j);
                    }
            return result;
        }
        else {
            std::cout << "Error" << std::endl;
            return *this;
        }
    }

    template<typename I, int P,int Q>
    Matrix& operator*=(Matrix<I,P,Q> temp){
        if(M == P) {
            std::cout << "Sub Work" << std::endl;
            Matrix result(N, Q);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < Q; j++)
                    for (int k = 0; k < M; k++) {
                        result.m_matrix[i][j] += m_matrix[i][k] * temp.GetEl(k, j);
                    }
            delete[] m_matrix;
            m_n = N;
            m_m = Q;
            m_matrix = new T*[m_n];

            for(int i=0;i<m_n;i++)
                m_matrix[i] = new T[m_m];

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_matrix[i][j] =result.m_matrix[i][j];
            return *this;
        }
        else {
            std::cout << "Error" << std::endl;
            return *this;
        }
    }

    Matrix& operator++() {
        for (int i = 0; i < m_n; i++)
            for (int j = 0; j < m_m; j++)
                m_matrix[i][j]+=1;
        return *this;
    }

    T* operator[](int n){
        return m_matrix[n];
    }

    Matrix Minor(int m){
        Matrix result(N-1, M-1);
        for(int i =0; i< N-1; i++)
            for(int j =0; j < M-1; j++) {
                if (j < m)
                    result.m_matrix[i][j] = m_matrix[i + 1][j];
                else
                    result.m_matrix[i][j] =  m_matrix[i + 1][j+1];
            }
        for(int i =0; i< N-1; i++) {
            for (int j = 0; j < M - 1; j++) {
                std::cout << result.m_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }

        return result;
    }

    double determinant()
    {
        double d = 0;
        std::cout << "Det Work" << std::endl;
        if(m_n == 1 && m_m == 1){
            return m_matrix[0][0];
        }
        if (m_n == 2 && m_m == 2)
        {
            d = m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
            std::cout << "Work 2x2 " << d << std::endl;
        }
        else
        {
            for(int j=0; j < M; j++){
                d += pow(-1,j) * m_matrix[0][j] * Minor(j).determinant();
                std::cout << "work" << std::endl;
            }
        }
        return d;
    }

    friend std::ostream& operator<<(std::ostream& out, Matrix& m) {
        for (int i = 0; i < m.m_n; i++) {
            for (int j = 0; j < m.m_m; j++)
                out << m.m_matrix[i][j] << " ";
            out << std::endl;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Matrix& m){
        for (int i = 0; i < m.m_n; i++)
            for (int j = 0; j < m.m_m; j++)
                in >> m.m_matrix[i][j];
        return in;
    }

    int GetEl(int n, int m){ return m_matrix[n][m]; }
    int GetN(){ return m_n;}
    int GetM(){ return m_m;}
};

using Matrix22i = Matrix<int, 2, 2>; // typedef
using Vector2i = Matrix<int, 2, 1>;

int main(){

    Matrix<int,3,3> M1(3,3);

    std::cin >> M1;
    M1[1][0] = 0;
    std::cout <<M1;
    //std::cout << M1.determinant();

    return 0;
}

/*
 1 2 3 4 5 6 7 8 9
 * */