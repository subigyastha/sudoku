#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace sf;
class rule
{public:
	void set(std::string s, Font& font) {
		Rule.setString(s);
		Rule.setFont(font);
		Rule.setCharacterSize(30);
		Rule.setFillColor(Color::White);
	}
	void setPos(Vector2f pos) {
		Rule.setPosition(pos);
	}
	void drawTo(sf::RenderWindow& window)
	{
		window.draw(Rule);
	

	}
private:
	Text Rule;
};

