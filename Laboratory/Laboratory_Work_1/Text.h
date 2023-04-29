//
// Created by vtakk on 03.02.2023.
//
#pragma once

namespace mt {
    class Text {
    private:
        sf::Font font;
        sf::Text text;
        std::string str;
        //int size = 30;
    public:
        Text() {
            if (!font.loadFromFile("C:/Users/vtakk/CLionProjects/2_semestr/LaboratoryWork_1/assets/beer-money12.ttf"))
            {
                std::cout << "error ";
            }

            text.setFont(font);
            text.setString(str);
            text.setCharacterSize(50);
            text.setFillColor(sf::Color(125, 0, 125, 0xFF));
            text.setPosition(100, 100);
        }

        ~Text() {}

        void SetString(char k) {
            //str.erase(str.end() - 1);
            str += k;
            text.setString(str);
        }

        sf::Text Get() { return text; }

        std::string GetString() { return text.getString(); }

    };
}
#ifndef LABORATORYWORK_1_TEXT_H
#define LABORATORYWORK_1_TEXT_H

#endif //LABORATORYWORK_1_TEXT_H
