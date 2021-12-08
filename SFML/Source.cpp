#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Menu.h"
using namespace sf;


int N = 30, M = 20;
float size = 16;

float width = (size * N);
float height = (size * M);



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
void Move(bool&);
void Run();
void PlayGame();
void GameOver();



int main()
{
    srand(time(0));
    Run();
    return 0;
}

void Move(bool& endGame)
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
    }

    if (snake[0].x > N) snake[0].x = 0;  if (snake[0].x < 0) snake[0].x = N;
    if (snake[0].y > M) snake[0].y = 0;  if (snake[0].y < 0) snake[0].y = M;

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
                        PlayGame();
                        break;
                    case 1:
                        std::cout << "Option button has been pressed" << std::endl;
                        break;
                    case 2:
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

void PlayGame()
{
    srand(time(0));


    Run();
    RenderWindow window(VideoMode(496, 336), "Snake Game!");


    Texture t1, t2;
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/red.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer = 0, delay = 0.1;

    f.x = 10;
    f.y = 10;
    bool endGame = false;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 0 ) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3) dir = 0;

        if (timer > delay) { timer = 0; Move(endGame); }

        if (endGame == true)
        {
            window.close();
            GameOver();
        }

        ////// draw  ///////
        window.clear();

        for (int i = 0; i < N+1; i++)
            for (int j = 0; j < M+1; j++)
            {
                sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
            }

        for (int i = 0; i < num; i++)
        {
            sprite2.setPosition(snake[i].x * size, snake[i].y * size);  window.draw(sprite2);
        }

        sprite2.setPosition(f.x * size, f.y * size);  window.draw(sprite2);

        window.display();
    }
}

void GameOver()
{
    RenderWindow window(VideoMode(width, height), "Game over!");
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
                    window.close();
                }

                break;
            case sf::Event::Closed:
                window.close();

                break;

            }
        }

        GameOver.setFont(Font);
        GameOver.setFillColor(sf::Color::Red);
        GameOver.setString("Game over");
        GameOver.setPosition(sf::Vector2f(width / 2 - width * 2/15, height / (2 + 1) * 1));

        HighScore.setFont(Font);
        HighScore.setFillColor(sf::Color::White);
        HighScore.setString("High Score:");
        HighScore.setPosition(sf::Vector2f(width / 2 - width * 2 / 15, height / (2 + 1) * 2));

        window.draw(GameOver);
        window.draw(HighScore);
        window.display();
    }
}