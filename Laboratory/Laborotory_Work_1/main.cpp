#include <iostream>
#include <C:/Users/vtakk/CLionProjects/2_semestr/LaboratoryWork_1/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <fstream>
#include "Text.h"

class AnimatedText{
private:
    std::vector<char> string;
    sf::Time duration;
    mt::Text text;
    int numbers;
    int count = 0;
public:
    AnimatedText(sf::Time d){
        duration = d;
        std::ifstream file("C:/Users/vtakk/CLionProjects/2_semestr/LaboratoryWork_1/HelloWorld.txt");
        if (!file)
            std::cout << "Error!" << std::endl;
        std::string word;
        while (file >> word) {
            for (int i = 0; i < word.length(); i++) {
                string.push_back(word[i]);
            }
            string.push_back(' ');
        }

        numbers = d.asSeconds()/string.size();
        std::cout << numbers;
    }

    void Change(float d){
        if(d>numbers and count <string.size()){
            text.SetString(string[count]);
            count++;
        }
    }


    void Draw(){
        sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
        sf::Clock timer0;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            sf::Time timer = timer0.getElapsedTime();
            Change(timer.asSeconds());
            if(timer.asSeconds() > numbers)
                timer0.restart();
            //std::cout << timer.asSeconds() << " ";

            window.clear();
            window.draw(text.Get());
            window.display();
        }
    }
};


int main() {
    AnimatedText anime(sf::seconds(13));
    anime.Draw();

    return 0;
}
