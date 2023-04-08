#include <iostream>
#include <vector>
#include <math.h>
#include <C:/Users/vtakk/CLionProjects/2_semestr/LaboratoryWork_1/SFML-2.5.1/include/SFML/Graphics.hpp>


//Программа должна хранить координаты и размеры фигуры, цвет, уметь вычислять площадь фигуры.
template<typename T>
struct coordinates{
    T x;
    T y;
};

template<typename Q>
class Shapes{
protected:
    coordinates<Q> sh_location;
    std::vector<int> sh_size;
    sf::Color sh_color;
public:
    Shapes(coordinates<Q> loc, std::vector<int>* size, sf::Color color): sh_location(loc), sh_size(*size), sh_color(color){
        std::cout << "Shape: ";
    }
    virtual ~Shapes(){
        std::cout<<"Destructor shapes" << std::endl;
    }

    virtual void square(){
        std::cout << "Shape square" << std::endl;
    }

    sf::Color GetColor(){ return sh_color; }

    void SetColor(sf::Color color) { sh_color = color;}
};

template<typename P>
class triangle: Shapes<P>{
public:
    triangle(coordinates<P> loc, std::vector<int>* size, sf::Color color): Shapes<P>(loc, size,color){
        std::cout << "triangle" << std::endl;
    }
    ~triangle() {
        std::cout << "Destructor triangle" << std::endl;
    }

    virtual void square(){
        std::cout << "Triangle square ";
        float p = float(this->sh_size[0] + this->sh_size[1] + this->sh_size[2]) / 2;
        float sq = sqrt(p * (p - this->sh_size[0]) * (p - this->sh_size[1]) * (p - this->sh_size[2]));
        std::cout << sq << std::endl;
    }
};

template<typename R>
class rectangle: Shapes<R>{
public:
    rectangle(coordinates<R> loc, std::vector<int>* size, sf::Color color): Shapes<R>(loc, size,color){
        std::cout << "Rectangle" << std::endl;
    }
    ~rectangle() {
        std::cout << "Destructor rectangle" << std::endl;
    }

    virtual void square(){
        std::cout << "Rectangle square ";
        float sq = this->sh_size[0] * this->sh_size[1];
        std::cout << sq << std::endl;
    }
};


template<typename R>
class circle: Shapes<R>{
public:
    circle(coordinates<R> loc, std::vector<int>* size, sf::Color color): Shapes<R>(loc, size,color){
        std::cout << "Circle" << std::endl;
    }
    ~circle() {
        std::cout << "Destructor circle" << std::endl;
    }

    virtual void square(){
        std::cout << "Circle square: ";
        float sq = this->sh_size[0] * this->sh_size[0] * M_PI;
        std::cout << sq << std::endl;
    }
};

int main() {
    std::vector<int> v={2,2,3};
    triangle<int> tr({1,1},&v,sf::Color::Black);
    tr.square();

    std::vector<int> v2={2,3};
    rectangle<int> rec({1,1},&v2,sf::Color::Black);
    rec.square();

    std::vector<int> v3={2};
    circle<int> c({1,1},&v3,sf::Color::Black);
    c.square();
    return 0;
}
