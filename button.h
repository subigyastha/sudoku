#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
class button
{
public:
	button(){}
	button(std::string t,sf::Color bgcolor, sf::Color color,sf::Vector2f size,int charSize)
	{
		text.setString(t);
		text.setCharacterSize(charSize);
		text.setFillColor(color);
		
		buttons.setSize(size);
		buttons.setFillColor(bgcolor);
	}
	void setPosition(sf::Vector2f pos)
	{
		buttons.setPosition(pos);
		float xPos = (pos.x + buttons.getLocalBounds().width /2) - (text.getLocalBounds().width / 2);
		float yPos= (pos.y + buttons.getLocalBounds().height / 2.5)- (text.getLocalBounds().height/ 2.5);
		text.setPosition({xPos,yPos});
	}
	void setFont(sf::Font &font) 
	{
		text.setFont(font);

	}
	void drawTo(sf::RenderWindow &window) 
	{
		window.draw(buttons);
		window.draw(text);

	}
	
	bool isMouseOver(sf::RenderWindow &window)
	{
		Vector2i mousePos = Mouse::getPosition(window);
		if (buttons.getGlobalBounds().contains(mousePos.x,mousePos.y))
		{
			return true;
		}
		return false;

	}

	float getGlobalBound() {
		return buttons.getGlobalBounds().width;
	}
	void setFillColors(sf::Color color) {
		buttons.setFillColor(color);
	}
	void set(Color color,Color c,string s,int i,Vector2f size) {
		buttons.setFillColor(color);
		text.setFillColor(c);
		text.setString(s);
		text.setCharacterSize(i);
		buttons.setSize(size);
	}

private:
	sf::Text text;
	sf::RectangleShape buttons;
};

