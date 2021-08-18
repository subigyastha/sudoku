#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<fstream>
#include"Player.h"
#include<iomanip>
using namespace std;
using namespace sf;

class Record
{
	public:

		Record(sf::Font &font)
		{
			PlayerText.setFont(font);
			PlayerText.setCharacterSize(30);

		}
		void setPos(sf::Vector2f pos) {
			PlayerText.setPosition(pos);
		}
		void getText(sf::RenderWindow &window,sf::Font &font)
		{
			text1.setFont(font);
			text2.setFont(font);
			text3.setFont(font);
			text1.setFillColor(Color::White);
			text2.setFillColor(Color::White);
			text3.setFillColor(Color::White);
			float count = 4;
			ifstream inFile;

			string name;
			string level;
			string time;

			inFile.open("PlayerRecord.csv");
			if (inFile.is_open()) {
				cout << "File has been opened" << endl;
			}
			else {
				cout << "NO FILE HAS BEEN OPENED" << endl;
			}

			while (!inFile.eof())
			{
				getline(inFile, name, ',');
				getline(inFile, level, ',');
				getline(inFile, time);
				

			   text1.setString(name);
			   text2.setString(level);
			   text3.setString(time);
			   text1.setPosition({ 200,count * 50 });
			   text2.setPosition({ 400,count * 50 });
			   text3.setPosition({ 600,count * 50 });
				window.draw(text1);
				window.draw(text2);
				window.draw(text3);
				count++;
				name = "";
				level = "";
				time = "";

			}
			inFile.close();
			
			
			
	
		 
		
		}
		
		
private:
	sf::Text PlayerText;
	Text text1, text2, text3;
	
	
	
	

};

