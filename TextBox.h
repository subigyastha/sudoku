#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESC_KEY 27

class TextBox
{
public:
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
	void setboundery(sf::Color color)
	{
		textBox.setOutlineColor(color);
	}
	void setPosition(sf::Vector2f pos)
	{
		textBox.setPosition(pos);
	}
	void setLimit(bool TOF)
	{
		hasLimit = TOF;
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
				newT = t[i];
			}
			textBox.setString(newT);
		}
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
			if (charTyped < 128)
			{
				if (hasLimit)
				{

					if (text.str().length() < limit)
					{
						inputLogic(charTyped);

					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY)
					{
						deletLastCharacter();
					}
					else
					{
						inputLogic(charTyped);
					}

				}
				else
				{
					inputLogic(charTyped);

				}

			}
		}
	}
	void drawBack(sf::RenderWindow &window,sf::Vector2f pos)
	{
		backGroundForm.setPosition(pos);
		backGroundForm.setSize({ 200,40 });
		backGroundForm.setFillColor(sf::Color(200, 200, 200, 100));
		window.draw(backGroundForm);
		
	
	}
	bool isMouseOver(sf::RenderWindow& window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (backGroundForm.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			return true;
		}
		return false;

	}
	void setFillColors(sf::Color color) {
		backGroundForm.setFillColor(color);
	}
public:
	std::string name;
	std::string roll;
	sf::RectangleShape backGroundForm;
private:
	
	sf::Text textBox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;
	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESC_KEY)
		{
			text << static_cast<char>(charTyped);

		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
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


