#include "Engine.h"
#include"button.h"
#include<iostream>
#include"Mtime.h"
#include"TextBox.h"
#include"Player.h"
string intTOstring(int number);
button tryAgain("TRY AGAIN", Color(200, 200, 200, 100),sf::Color::White,sf::Vector2f(200,40),20);
button solve("SOLVE", Color(200, 200, 200, 100), sf::Color::White, sf::Vector2f(200, 40), 20);
button menu("MENU", Color(200, 200, 200, 100), sf::Color::White, sf::Vector2f(200, 40), 20);
button submit("SUBMIT", Color(200, 200, 200, 100), sf::Color::White, sf::Vector2f(200, 40), 20);
TextBox namebox(15, sf::Color::Black, true);
Player player;


void Engine::starttime() {
	if (clockreset)
		Engine::clock.restart();//if its first time running this loop then rest the clock 
	clockreset = false;//then make the reset bool false
	Engine::tm = clock.getElapsedTime();//string the time elasped by the clock in the time variable
}
Text Engine::displaytime() {
	std::system("CLS");
	std::cout << (int)tm.asSeconds() << std::endl;
	Mtime tem = (int)tm.asSeconds();
	tem.gettime();
	string times = "Time : " + intTOstring(tem.Rhour()) + ":" + intTOstring(tem.Rminute()) + ":" + intTOstring(tem.Rsecond());
	Text timedisplay(times, font, 40);
	timedisplay.setPosition(10, 10);
	timedisplay.setFillColor(Color(255, 255, 255, 200));
	return timedisplay;
}

Engine::Engine()
{
	
	

	srand(time(NULL));

	font.loadFromFile("arial.ttf");
	texture.loadFromFile("back.png");

	Game game;
	state = GAME;
}

Engine::~Engine()
{
}

string intTOstring(int number)
{
	if (number == 0)
		return "0";
	string temp = "";
	string returnvalue = "";
	while (number > 0)
	{
		temp += number % 10 + 48;
		number /= 10;
	}
	for (int i = 0; i < temp.length(); i++)
	{
		returnvalue += temp[temp.length() - i - 1];
	}

	return returnvalue;
}
bool Engine::runEngine(RenderWindow& window, int level)
{
	bool once = true;
	Sprite background(texture);

	int size = 9;
	int index = 0;

	int** m = new int* [20];
	m[0] = new int[20 * 20];

	for (int i = 1; i < 20; i++)
	{
		m[i] = m[i - 1] + 20;
	}

	bool** b = new bool* [20];
	b[0] = new bool[20 * 20];

	for (int i = 1; i < 20; i++)
	{
		b[i] = b[i - 1] + 20;
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			b[i][j] = true;
		}

	}

	fillTable(m, size, window);
	setLevel(m, b, size, level);

	Input input;
	input.val = 0;
	input.value = "";

	CellSize = 40;
	FontSize = 20;

	while (window.isOpen())
	{

		Event event;
		// while there are pending events...

		starttime();
		while (window.pollEvent(event) && state == GAME)
		{

			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case Event::Closed:
				delete[]m[0];
				delete[]b[0];
				window.close();
				break;

			case Event::KeyPressed:

				if ((Keyboard::isKeyPressed(Keyboard::Escape)))
				{
					delete[]m[0];
					delete[]b[0];
					return false;
				}
			case Event::MouseButtonPressed:
			{	if (tryAgain.isMouseOver(window))
				reset(m, b, size);
			else if (solve.isMouseOver(window))
			{
				solveb = true;
				reset(m, b, size);
				solveSudoku(window, m, b, size);


			}
			else if (menu.isMouseOver(window))
			{
				delete[]m[0];
				delete[]b[0];
				return false;
			}
			else if (namebox.isMouseOver(window))
			{
				namebox.setSelected(true);
				if (event.type == sf::Event::TextEntered) {
					namebox.typedOn(event);

				}
			}

			}
			selectCell(window, size, index, m, b, input);
			break;

			default:
				break;
			}

		}

		{
			if (tryAgain.isMouseOver(window))

				tryAgain.setFillColors(Color(200, 200, 200, 230));
			else
				tryAgain.setFillColors(Color(200, 200, 200, 100));


			if (solve.isMouseOver(window))

				solve.setFillColors(Color(200, 200, 200, 230));
			else
				solve.setFillColors(Color(200, 200, 200, 100));

			if (menu.isMouseOver(window))

				menu.setFillColors(Color(200, 200, 200, 230));
			else
				menu.setFillColors(Color(200, 200, 200, 100));
			if (submit.isMouseOver(window))
				submit.setFillColors(Color(200, 200, 200, 230));
			else
				submit.setFillColors(Color(200, 200, 200, 100));




			namebox.setFont(font);
			namebox.setPosition({ 715,415 });
			namebox.setFillColors(Color(0, 0, 0));

			tryAgain.setPosition({ 700,300 });
			tryAgain.setFont(font);
			solve.setPosition({ 700,250 });
			solve.setFont(font);
			menu.setPosition({ 700,350 });
			menu.setFont(font);
			if (submit.isMouseOver(window))
				submit.setPosition({ 700,460 });
			else
				submit.setPosition({ 700,465 });
			submit.setFont(font);
		}
		window.clear();
		window.draw(background);

		tryAgain.drawTo(window);
		solve.drawTo(window);
		menu.drawTo(window);




		drawSquare(window, m, b, size, index);

		input.cell.setCharacterSize(20);
		input.cell.setFillColor(Color(80, 80, 80));
		input.cell.setFont(font);
		input.cell.setString(input.value);
		input.cell.setPosition(10, 10);
		input.cell.setPosition((400 - size / 2 * CellSize) + index % size * CellSize + FontSize / 2, (300 - size / 2 * CellSize) + index / size * CellSize + FontSize / 2);

		window.draw(input.cell);

		if (checkWin(m, size))
			state = GAMEOVER;

		if (state == GAMEOVER)
		{
			int x;//x psotion of text
			if (endreset)
				endtm = tm;//store end time
			endreset = false;
			tm = endtm;//set displaying time to endtime
			string texto = "";
			//logic for set psoition
			if (!solveb) {
				texto = "Congratulation";
				x = 230;
			}
			else {
				x = 320;
				texto = "Solved";
			}
			Text conteudo(texto, font, 60);
			conteudo.setPosition(x, 50);
			conteudo.setFillColor(Color(80, 80, 80));
			if (solveb)//to show or not to show submit button
			{
				namebox.drawBox(window);
				namebox.drawTo(window);
				submit.drawTo(window);
			}
			window.draw(conteudo);


			if ((Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed))
			{

				delete[]m[0];
				delete[]b[0];
				window.close();

			}

			if (namebox.isMouseOver(window) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				namebox.setSelected(true);
				namebox.setLimit(true, 6);
			}

			if (event.type == sf::Event::TextEntered && namebox.selectornot()) {
				//std::cout << event.text.unicode;
				namebox.typedOn(event);
			}


			if (submit.isMouseOver(window) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				player.setname(namebox.getText());
				player.setDifficluty(level);
				player.setTime((int)endtm.asSeconds());
				std::cout << player.getname() << std::endl;
				std::cout << player.getDifficulty() << std::endl;
				player.getTime().gettime();
				if (once)
				{
					player.writeToFile(player.getname(), player.getDifficulty(), player.getTime(), once);
				}
				delete[]m[0];
				delete[]b[0];
				player.setname("");
				namebox.reset();
				return false;


			}
				if (menu.isMouseOver(window) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
				{
					delete[]m[0];
					delete[]b[0];
					player.setname("");
					namebox.reset();
					return false;
					
				}

			




			}
		window.draw(displaytime());
		window.display();
		}
			
		
		return true;


	}


bool Engine::checkRow(int** m, int size, int row, int value)
{
	for (int i = 0; i < size; i++)
	{
		if (m[row][i] == value)
		{
			return false;
		}
	}
	return true;
}

bool Engine::checkColumn(int** m, int size, int column, int value)
{
	for (int i = 0; i < size; i++)
	{
		if (m[i][column] == value)
		{
			return false;
		}
	}
	return true;
}

bool Engine::checkSquare(int** m, int tamanho, int row, int column, int value)
{
	int quadx = 3, quady = 3;

	int sizey = row / quady;
	int sizex = column / quadx;


	sizey = (sizey * quady);
	sizex = (sizex * quadx);

	for (int i = sizey; i < sizey + quady; i++)
	{
		for (int j = sizex; j < sizex + quadx; j++)
		{
			if (m[i][j] == value)
			{
				return false;
			}
		}
	}
	return true;

}

bool Engine::removing(bool bol[16], int t)
{
	for (int i = 0; i < t; i++)
	{
		if (bol[i])
		{
			return false;
		}
	}
	return true;
}

void Engine::selectCell(RenderWindow& window, int size, int& index, int** matrix, bool** bloc, Input& input)
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{

		index--;

		if (index < 0)
		{
			index = size * size - 1;


		}
		input.value = "";
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		index++;

		if (index > size * size - 1)
		{
			index = 0;

		}
		input.value = "";
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		index -= size;

		if (index < 0)
		{
			index = ((size * size)) - size + ((index + size) % size);

		}
		input.value = "";
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		index += size;

		if (index > size * size - 1)
		{
			index = index % size;

		}
		input.value = "";
	}
	if (!bloc[index / size][index % size] && input.value.size() <= 1)
	{
		if (Keyboard::isKeyPressed(Keyboard::Num0) || Keyboard::isKeyPressed(Keyboard::Numpad0))
		{
			input.value += '0';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1))
		{
			input.value += '1';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2))
		{
			input.value += '2';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3))
		{
			input.value += '3';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4))
		{
			input.value += '4';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5))
		{
			input.value += '5';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Numpad6))
		{
			input.value += '6';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num7) || Keyboard::isKeyPressed(Keyboard::Numpad7))
		{
			input.value += '7';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Numpad8))
		{
			input.value += '8';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num9) || Keyboard::isKeyPressed(Keyboard::Numpad9))
		{
			input.value += '9';
		}

	}

	if (!bloc[index / size][index % size])
	{
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			input.val = atoi(input.value.c_str());

			bool correct;

			correct = checkColumn(matrix, size, index % size, input.val) && checkRow(matrix, size, index / size, input.val) && checkSquare(matrix, size, index / size, index % size, input.val);

			if (input.val > 0 && input.val <= size && correct)
			{
				matrix[index / size][index % size] = input.val;
				input.value = "";
			}
			else
			{
				input.value = "";
			}
		}
		
	}
}



void Engine::drawSquare(RenderWindow& window, int** matrix, bool** bloc, int size, int index)
{
	int quadx = 3, quady = 3;

	int cellSize = 40, fontSize = 20;

	Font font;
	font.loadFromFile("arial.ttf");

	RectangleShape mediumSquare;
	mediumSquare.setSize(Vector2f(cellSize * quadx, cellSize * quady));
	mediumSquare.setOutlineThickness(2);
	mediumSquare.setOutlineColor(sf::Color::Black);
	//quadradog.setOutlineColor(sf::Color::Red);
	mediumSquare.setFillColor(sf::Color::Transparent);

	RectangleShape bigSquare;
	bigSquare.setSize(Vector2f(cellSize * size, cellSize * size));
	bigSquare.setOutlineThickness(4);
	bigSquare.setOutlineColor(sf::Color::Black);
	//quadradofull.setOutlineColor(sf::Color::Red);
	bigSquare.setFillColor(sf::Color::Transparent);
	bigSquare.setPosition((400 - size / 2 * cellSize), (300 - size / 2 * cellSize));

	RectangleShape smallSquare;
	smallSquare.setSize(Vector2f(cellSize, cellSize));
	smallSquare.setOutlineThickness(1);
	smallSquare.setOutlineColor(Color(220,220,220));
	smallSquare.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			smallSquare.setPosition((400 - size / 2 * cellSize) + j * cellSize, (300 - size / 2 * cellSize) + i * cellSize);
			window.draw(smallSquare);
			string text;
			if (matrix[i][j] > 0)
			{
				text = intTOstring(matrix[i][j]);
			}
			else
			{
				text = "";
			}
			if (index % size == j && index / size == i)
			{
				smallSquare.setFillColor(Color(200,200,200));
				smallSquare.setPosition((400 - size / 2 * cellSize) + j * cellSize, (300 - size / 2 * cellSize) + i * cellSize);
				window.draw(smallSquare);
				smallSquare.setFillColor(sf::Color::Transparent);
			}

			Text cell(text, font, fontSize);
			cell.setPosition((400 - size / 2 * cellSize) + j * cellSize + fontSize / 2, (300 - size / 2 * cellSize) + i * cellSize + fontSize / 2);
			if (bloc[i][j])
			{
				cell.setFillColor(Color(80, 80, 80));
			}
			else
			{
				cell.setFillColor(Color::Blue);
			}


			window.draw(cell);
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i % quady == 0 && j % quadx == 0)
			{
				mediumSquare.setPosition((400 - size / 2 * cellSize) + j * cellSize, (300 - size / 2 * cellSize) + i * cellSize);
				window.draw(mediumSquare);
			}
		}
	}
	window.draw(bigSquare);
}

void Engine::fillTable(int** m, int& size, RenderWindow& window)
{

	int val[16];
	bool valbool[16];


	for (int i = 0; i < 16; i++)
	{
		val[i] = i + 1;
		valbool[i] = true;
	}

	int valueRow = (rand() % size);
	int reset = 0;


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{

			if (valbool[valueRow])
			{
				bool check;

				check = checkRow(m, size, i, val[valueRow]) && checkColumn(m, size, j, val[valueRow]) && checkSquare(m, size, i, j, val[valueRow]);

				if (check)
				{
					m[i][j] = val[valueRow];
					for (int i = 0; i < 16; i++)
					{
						valbool[i] = true;
					}
					valueRow = (rand() % size);
				}
				else
				{
					valbool[valueRow] = false;
					j--;
					valueRow = (valueRow + 1) % size;
				}
			}
			else
			{
				valueRow = (valueRow + 1) % size;
				j--;
				if (removing(valbool, size))
				{
					for (int x = 0; x < 16; x++)
					{
						valbool[x] = true;
						m[i][x] = 0;
					}
					reset++;
					j = -1;
					if (reset > 1000)
					{
						i = -1;
						j = -1;
						reset = 0;
						for (int i2 = 0; i2 < size; i2++)
						{
							for (int j2 = 0; j2 < size; j2++)
							{
								m[i2][j2] = 0;
							}
						}
						break;
					}
				}
			}
		}
	}

}

void Engine::setLevel(int** m, bool** b, int size, int difficulty)
{
	int amount;
	switch (difficulty)
	{
	case 0:
		amount = 2;
		break;
	case 1:
		amount = 3;
		break;
	case 2:
		amount = 5;
		break;
	default:
		amount = 2;
		break;
	}
	int numberCells = (size * size);
	int left = numberCells / amount;
	int deleted = numberCells - left;

	int row = rand() % size;
	int column = rand() % size;
	for (int i = 0; i < deleted; i++)
	{
		if (m[row][column] > 0)
		{
			m[row][column] = 0;
			b[row][column] = false;
		}
		else
		{
			row = rand() % size;
			column = rand() % size;
			i--;
		}
	}


}







bool Engine::checkWin(int** m, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (m[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
void Engine::reset(int** m, bool** b, int size)
{


	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {
			if (b[i][j] == false)
				m[i][j] = 0;
		}
	}



}
int Engine::findmty(int** m, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (m[i][j] == 0) {
				return i * size + j;
			}
		}
	}
	return -1;
}
bool Engine::solveSudoku(RenderWindow &window ,int** m, bool** b, int size)
{
	int row, col;
	int index = findmty(m, size);
	if (index == -1) return true;
	else
	{
		row = index / size;
		col = index % size;
	}
	for (int i = 1; i <= size; i++)
	{
		bool correct;
		correct = checkColumn(m, size, col, i) && checkRow(m, size, row, i) && checkSquare(m, size, row, col, i);
		if (correct)
		{

			m[row][col] = i;
			


			if (solveSudoku(window,m, b, size))
			{
				return true;
			}
			m[row][col] = 0;
		}
	}
	return false;
}



