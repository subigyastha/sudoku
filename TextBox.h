#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESC_KEY 27
using namespace sf;

class TextBox
{
public:
    std::string name;
    std::string roll;
    TextBox()
    {

    }
    TextBox(int size, sf::Color color, bool select) {

        textBox.setCharacterSize(size);
        textBox.setFillColor(color);
        isSelected = select;
        if (select) {
            textBox.setString("_");

        }
        else {
            textBox.setString("");
        }
    }
    void setFont(sf::Font& font)
    {
        textBox.setFont(font);
    }

    void setFillColors(sf::Color color) {
        textBox.setFillColor(color);
    }

    void drawBox(sf::RenderWindow& window) {

        txtBox.setSize(sf::Vector2f(190, textBox.getCharacterSize() + 20));
        txtBox.setOutlineColor(sf::Color(200, 200, 200, 150));
        txtBox.setFillColor(sf::Color::White);
        txtBox.setOutlineThickness(5);
        txtBox.setPosition(POS.x - 10, POS.y - 10);
        window.draw(txtBox);
    }
    void setboundery(sf::Color color)
    {
        textBox.setOutlineColor(color);
    }
    void setPosition(sf::Vector2f pos)
    {
        textBox.setPosition(pos);
        POS = pos;
    }

    void setLimit(bool TOF)
    {
        hasLimit = TOF;
        limit = 5;
    }
    void setLimit(bool TOF, int lim)
    {
        hasLimit = TOF;
        limit = lim;
    }
    void setSelected(bool sel)
    {
        isSelected = sel;
        if (!sel)
        {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length() - 1; i++)
            {
                newT += t[i];
            }
            textBox.setString(newT);
        }
    }
    void reset() {
        textBox.setString("");
        isSelected = false;
        text.str("");
    }
    std::string getText() {
        return text.str();

    }

    void drawTo(sf::RenderWindow& window)
    {
        window.draw(textBox);
    }
    void typedOn(sf::Event evnt)
    {
        if (isSelected) {
            int charTyped = evnt.text.unicode;
            if ((charTyped < 128 && charTyped>64) || charTyped == DELETE_KEY)
            {
                if (hasLimit)
                {

                    if (text.str().length() < limit)
                    {
                        inputLogic(charTyped);

                    }
                    else if (text.str().length() >= limit && charTyped == DELETE_KEY)
                    {
                        deletLastCharacter();
                    }
                }
                else
                {
                    inputLogic(charTyped);

                }

            }
        }
    }
    bool isMouseOver(sf::RenderWindow& window)
    {
        Vector2i mousePos = Mouse::getPosition(window);
        if (txtBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            return true;
        }
        return false;

    }
    bool selectornot() {
        return isSelected;
    }

private:

    sf::Text textBox;
    sf::RectangleShape txtBox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit;
    sf::Vector2f POS;
    void inputLogic(int charTyped) {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESC_KEY || charTyped == 105)
        {
            text << static_cast<char>(charTyped);

        }
        else if (charTyped == DELETE_KEY && charTyped != 105)
        {
            if (text.str().length() > 0)
            {
                // std::cout << "deleted";
                deletLastCharacter();
            }

        }
        else if (charTyped == ENTER_KEY)
        {
            name = text.str();
        }
        textBox.setString(text.str() + "_");
    }
    void deletLastCharacter()
    {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++)
        {
            newT += t[i];
        }
        text.str("");
        text << newT;
        textBox.setString(text.str());
    }



};