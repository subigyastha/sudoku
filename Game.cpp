#include "Game.h"
#include"button.h"
#include"rules.h"
#include"Engine.h"
#include"Record.h"

sf::RenderWindow window(VideoMode(1000, 800), "Sudoku", sf::Style::Titlebar | sf::Style::Close);



Game::Game()
{
	texture.loadFromFile("back.png");
	
	state = END;

	if (!font.loadFromFile("arial.ttf"))
		return;

	state = MENU;
}


Game::~Game(void)
{
}


void Game::runGame()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::AUTHOR:
			author();
			break;
		case GameState::GAME:
			levels();
			break;
		case GameState::RULES:
			rules();
			break;
		case GameState::RECORD:
			playerRecord();
			break;
		}
		
	}
}

void Game::playerRecord()
{
	Record r(font);
	Text title("Record", font, 80);
	title.setStyle(Text::Bold);
	
	
	Sprite background(texture);
	button back("Back", Color(200, 200, 200, 100), sf::Color::White, sf::Vector2f(200, 60), 35);
	back.setFont(font);
	back.setPosition({ 700,670 });


	while (window.isOpen() && state == RECORD)
	{

		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed)
				window.close();
			if (evnt.type == sf::Event::MouseButtonReleased && back.isMouseOver(window) && evnt.key.code == Mouse::Left)
				state = MENU;


		}

		if (back.isMouseOver(window))
			back.setFillColors(Color(200, 200, 200, 230));
		else
			back.setFillColors(Color(200, 200, 200, 100));

		

		window.clear();
		

		window.draw(background);
		r.getText(window,font);

		window.draw(title);
		back.drawTo(window);

		window.display();
	}

}
void Game::rules()
{
	Text title("Rules", font, 80);
	title.setStyle(Text::Bold);
	const String r[] = { "1) Every square has to contain a single number",
"2) Only the numbers from 1 through to 9 can be used",
"3) Each 3×3 box can only contain each number from 1 to 9 once",
"4) Each vertical column can only contain each number from 1 to 9 once",
"5) Each horizontal row can only contain each number from 1 to 9 once" };
	rule Rules[5];
	for (int i = 0; i < 5; i++) {
		Rules[i].set(r[i], font);
	}
	Sprite background(texture);
	button back("Back", Color(200, 200, 200, 100), sf::Color::White, sf::Vector2f(200, 60), 35);
	back.setFont(font);
	back.setPosition({ 700,670 });


	while (window.isOpen() && state == RULES)
	{

		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed)
				window.close();
			if (evnt.type == sf::Event::MouseButtonReleased && back.isMouseOver(window) &&evnt.key.code==Mouse::Left)
				state = MENU;


		}

		if (back.isMouseOver(window))
			back.setFillColors(Color(200, 200, 200, 230));
		else
			back.setFillColors(Color(200, 200, 200, 100));

		for (int i = 0; i < 5; i++) {
			Rules[i].setPos({ 20,(float)(i+3.5) * 40 });
		}

		window.clear();
		
		window.draw(background);
		for (int i = 0; i < 5; i++) {
			Rules[i].drawTo(window);
		}
		window.draw(title);
		back.drawTo(window);

		window.display();
	}

}


void Game::menu()
{
	Sprite background(texture);
	//window.setFramerateLimit(60);
	Text title("Sudoku", font, 80);
	title.setStyle(Text::Bold);

	title.setPosition(1000 / 2 - title.getGlobalBounds().width / 2, 60);

	const int ile = 5;

	button btn[ile];

	string str[] = { "Play","Author","Rules","Record","Exit"};
	for (int i = 0; i < ile; i++)
	{
		btn[i].set(Color(200,200,200,150),Color::White, str[i], 30, {300,70});
		btn[i].setFont(font);
		
		btn[i].setPosition({355,(float)(i+1.8) * 100 });
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;

			//klikniêcie MENU                                        
			else if (btn[0].isMouseOver(window)&&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME;
			}

			//klikniecie AUTHOR
			else if (btn[1].isMouseOver(window) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = AUTHOR;
			}
			else if (btn[2].isMouseOver(window) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = RULES;
			}
			//klikniêcie EXIT
			else if (btn[3].isMouseOver(window) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = RECORD;
			}
			else if (btn[4].isMouseOver(window) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
		}
		for (int i = 0; i < ile; i++)
			if (btn[i].isMouseOver(window))
				btn[i].setFillColors(Color(200,200,200,230));
			else btn[i].setFillColors(Color(200,200,200,100));

		window.clear();
		
		window.draw(background);
		window.draw(title);
	
		for (int i = 0; i < ile; i++)
		{
		
			btn[i].drawTo(window);
		}

		window.display();
	}
}

void Game::levels()
{
	Sprite background(texture);
	sf::Text title("Levels", font, 90);
	title.setStyle(sf::Text::Bold);

	title.setPosition(1000 / 2 - title.getGlobalBounds().width / 2, 30);
	title.setStyle(sf::Text::Bold);

	string easy, medium, hard;
	const int size = 4;
	button btn[size];

	std::string aut[] = { "Easy","Medium","Hard", "back" };
	for (int i = 0; i < size; i++)
	{
		btn[i].set(Color(200, 200, 200, 150), Color::White, aut[i], 30, { 300,70 });
		btn[i].setFont(font);

		btn[i].setPosition({ 355,(float)(i + 1.8) * 100 });
	}


	while (state == GAME && window.isOpen())
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		Engine engine;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (btn[0].isMouseOver(window) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (engine.runEngine(window, 0))
					state = GAME;
				else
					state = MENU;
			}

			else if (btn[1].isMouseOver(window) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				if (engine.runEngine(window, 1))
					state = GAME;
				else
					state = MENU;
			}

			else if (btn[2].isMouseOver(window) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				if (engine.runEngine(window, 2))
					state = GAME;
				else
					state = MENU;
			}

			else if (btn[3].isMouseOver(window) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = MENU;
			}
		}

		for (int i = 0; i < size; i++)
			if (btn[i].isMouseOver(window))
				btn[i].setFillColors(Color(200, 200, 200, 230));
			else btn[i].setFillColors(Color(200, 200, 200, 100));


		window.clear();
		window.draw(background);

		window.draw(title);
	
		for (int i = 0; i < size; i++)
			btn[i].drawTo(window);
		window.display();
	}

}

void Game::author()
{
	Sprite background(texture);
	sf::Text title("Author", font, 90);
	title.setStyle(sf::Text::Bold);

	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 60);
	title.setStyle(sf::Text::Bold);


	button back("Back", Color(200, 200, 200, 100), sf::Color::White, sf::Vector2f(200, 60), 35);
	back.setFont(font);
	back.setPosition({ 700,670 });
	
	


	while (state == AUTHOR && window.isOpen())
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//klikniecie EXIT
			
			if (back.isMouseOver(window) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
				state = MENU;
			}
		}

		if (back.isMouseOver(window))
			back.setFillColors(Color(200, 200, 200, 230));
		else
			back.setFillColors(Color(200, 200, 200, 100));


		window.clear();
		window.draw(background);
		window.draw(title);
		
		
		
		back.drawTo(window);
			
		window.display();
	}
}
