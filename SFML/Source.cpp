#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Menu.h"
#include <fstream>
#include <Windows.h>
#include <conio.h>

using namespace sf;


int N = 30, M = 20;
float size = 16;

float width = (size * N) + 160;
float height = (size * M) + +16;



struct Snake
{
	int x, y;
}  snake[100];

struct Fruit
{
	int x, y;
} f;

//Local var



int dir, num = 4;
//Func
void Move(bool&, bool&, bool);
void Run();
void PlayGame(RenderWindow&, int, bool);
void GameOver(RenderWindow&, int);
void Guide(RenderWindow&);
void Info(RenderWindow&);
int HardCore(RenderWindow&);

bool Classic(RenderWindow&);



int main()
{
	srand(time(0));
	Run();
	return 0;
}

void Move(bool& endGame, bool& isEat, bool classic)
{
	for (int i = num; i > 0; --i)
	{
		snake[i].x = snake[i - 1].x; snake[i].y = snake[i - 1].y;
	}

	if (dir == 0) snake[0].y += 1;
	if (dir == 1) snake[0].x -= 1;
	if (dir == 2) snake[0].x += 1;
	if (dir == 3) snake[0].y -= 1;

	if ((snake[0].x == f.x) && (snake[0].y == f.y))
	{
		num++; f.x = rand() % N; f.y = rand() % M;
		isEat = true;
	}


	if (snake[0].x > N)
	{
		if (classic == true)
			snake[0].x = N;
		else
		{
			endGame = true;
		}
	}
	if (snake[0].x < 0)
	{
		if (classic == true)
			snake[0].x = N;
		else
		{
			endGame = true;
		}
	}
	if (snake[0].y > M)
	{
		if (classic == true)
			snake[0].y = 0;
		else
		{
			endGame = true;
		}
	}
	if (snake[0].y < 0)
	{
		if (classic == true)
			snake[0].y = M;
		else
		{
			endGame = true;
		}
	}


	for (int i = 1; i < num; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)  num = i;
		if (i != 0 && (snake[0].x == snake[i].x && snake[0].y == snake[i].y))
			endGame = true;
	}
}

void Run()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Snake Game!");

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						PlayGame(window, HardCore(window), Classic(window));
						break;
					case 1:
						std::cout << "High button has been pressed" << std::endl;
						break;
					case 2:
						Guide(window);
						break;
					case 3:
						Info(window);
						break;
					case 4:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();

		menu.draw(window);

		window.display();
	}
}

bool Classic(RenderWindow& window)
{
	Font Font;
	Font.loadFromFile("arial.ttf");
	Text classic;
	Text wall;
	int hardCore = 1;
	bool cMode = true;
	classic.setFont(Font);
	classic.setFillColor(sf::Color::Red);
	classic.setString("Classic mode");
	classic.setCharacterSize(30);
	classic.setPosition(sf::Vector2f(width / 2 - 100, 100));

	wall.setFont(Font);

	wall.setString("Wall mode");
	wall.setCharacterSize(30);
	wall.setPosition(sf::Vector2f(width / 2 - 100, 140));
	wall.setFillColor(sf::Color::White);
	while (window.isOpen())
	{

		
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					cMode = !cMode;
					if (cMode == true)
					{
						classic.setFillColor(sf::Color::Red);
						wall.setFillColor(sf::Color::White);
					}
					else
					{
						classic.setFillColor(sf::Color::White);
						wall.setFillColor(sf::Color::Red);
					}
					break;
				case sf::Keyboard::Down:
					cMode = !cMode;
					if (cMode == true)
					{
						classic.setFillColor(sf::Color::Red);
						wall.setFillColor(sf::Color::White);
					}
					else
					{
						classic.setFillColor(sf::Color::White);
						wall.setFillColor(sf::Color::Red);
					}
					break;
				case sf::Keyboard::Return:
					return cMode;
				}
				break;
			case sf::Event::Closed:
				window.close();

				break;
			}
		}
		window.clear();

		window.draw(classic);
		window.draw(wall);
		window.display();
	}
}

int HardCore(RenderWindow& window)
{
	Font Font;
	Font.loadFromFile("arial.ttf");
	Text HardCore;
	int hardCore = 1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Enter:
					return hardCore;
					break;
				case sf::Keyboard::Right:
					hardCore += 1;
					if (hardCore > 10) hardCore = 1;
					break;
				case sf::Keyboard::Left:
					hardCore -= 1;
					if (hardCore < 1) hardCore = 10;
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();

				break;
			}
		}
		window.clear();
		HardCore.setFont(Font);
		HardCore.setFillColor(sf::Color::Blue);
		std::string textPoint = "Level of difficult:\t < " + std::to_string(hardCore) + " >";
		HardCore.setString(textPoint);
		HardCore.setCharacterSize(30);
		HardCore.setPosition(sf::Vector2f(width / 2 - 150, 100));
		window.draw(HardCore);
		window.display();
	}

}

void PlayGame(RenderWindow& window, int hardCore, bool classic)
{
	srand(time(0));




	Texture t1, t2;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);

	Clock clock;
	float timer = 0, delay = 0.13 - 0.01 * hardCore;

	f.x = 10;
	f.y = 10;
	Font Font;
	Font.loadFromFile("arial.ttf");
	Text HighScore;
	bool endGame = false;
	bool space = false;
	int point = 0;
	bool isEat = false;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event event;
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					space = !space;
					break;
				case sf::Keyboard::Escape:
					return;
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}
		if (space == true) continue;
		if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2) dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1) dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 0) dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3) dir = 0;

		if (timer > delay) { timer = 0; Move(endGame, isEat, classic); }

		if (endGame == true)
		{
			GameOver(window, point);
			return;
		}

		if (isEat == true)
		{
			point += 10;
			isEat = false;
		}

		////// draw  ///////
		window.clear();

		for (int i = 0; i < N + 1; i++)
			for (int j = 0; j < M + 1; j++)
			{
				sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
			}

		for (int i = 0; i < num; i++)
		{
			sprite2.setPosition(snake[i].x * size, snake[i].y * size);  window.draw(sprite2);
		}

		sprite2.setPosition(f.x * size, f.y * size);  window.draw(sprite2);
		HighScore.setFont(Font);
		HighScore.setFillColor(sf::Color::White);
		std::string textPoint = "High Score\n" + std::to_string(point);
		HighScore.setString(textPoint);
		HighScore.setCharacterSize(20);
		HighScore.setPosition(sf::Vector2f(width - 130, 50));
		window.draw(HighScore);
		window.display();
	}
}

void GameOver(RenderWindow& window, int point)
{
	Text GameOver;
	Font Font;
	Font.loadFromFile("arial.ttf");
	Text HighScore;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					return;
				case sf::Keyboard::Escape:
					return;
					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}
		window.clear();

		GameOver.setFont(Font);
		GameOver.setFillColor(sf::Color::Red);
		GameOver.setString("Game over");
		GameOver.setPosition(sf::Vector2f(width / 2 - width * 2 / 15, height / (2 + 1) * 1));

		HighScore.setFont(Font);
		HighScore.setFillColor(sf::Color::Red);
		HighScore.setString("Score: " + std::to_string(point));
		HighScore.setPosition(sf::Vector2f(width / 2 - width * 2 / 15, height / (2 + 1) * 2));

		window.draw(GameOver);
		window.draw(HighScore);
		window.display();
	}
}

void Guide(RenderWindow& window)
{
	Text GameGuide;
	Font Font;
	Font.loadFromFile("arial.ttf");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					return;
				case sf::Keyboard::Escape:
					return;
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}
		window.clear();

		std::ifstream FileIn("TextGame.dll", std::ios::in);
		int line = 15;
		std::string guide;
		while (!FileIn.eof())
		{
			std::string text;
			std::getline(FileIn, text);
			if (text == "**")
				break;
			guide += text + "\n";

		}
		GameGuide.setFont(Font);
		GameGuide.setCharacterSize(25);
		GameGuide.setFillColor(sf::Color::Green);
		GameGuide.setString(guide);
		window.draw(GameGuide);
		window.display();
	}
}

void Info(RenderWindow& window)
{
	Text GameInfo;
	Font Font;
	Font.loadFromFile("arial.ttf");
	std::string text1 = "\t\tTran Anh Hao - 20521295\n";
	std::string text2 = "\t\tPham Van Khanh - 20521456\n";
	std::string text3 = "\t\tDin Hien Dung - 20521205\n";
	std::string text4 = ">>-----Thanks you for play game-----<<";
	std::string text = text1 + text2 + text3 + text4;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					return;
				case sf::Keyboard::Escape:
					return;
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}
		window.clear();

		GameInfo.setFont(Font);
		GameInfo.setCharacterSize(25);
		GameInfo.setFillColor(sf::Color::Green);
		GameInfo.setString(text);
		GameInfo.setPosition(sf::Vector2f(width / 2 - width / 3, 20));
		window.draw(GameInfo);
		window.display();
	}
}
