#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>


//size of the window
#define LENGTH 80 
#define WIDTH 60

using namespace sf;

int size = 16;
int w = size * LENGTH;
int h = size * WIDTH;
int direction = 0, tail = 4, gameLost;


//positioning - declared ring and golum
struct position
{
	int x;
	int y;
}ring[100], golum;;

void CheckDirection()
{
	if (direction == 0)
	{
		ring[0].y++;
	}
	if (direction == 1)
	{
		ring[0].x--;
	}
	if (direction == 2)
	{
		ring[0].x++;
	}
	if (direction == 3)
	{
		ring[0].y--;
	}
}

//void of the game
void game()
{
	for (int i = tail; i > 0; i--)
	{
		ring[i].x = ring[i - 1].x;
		ring[i].y = ring[i - 1].y;

	}
	
	
	CheckDirection();





	
	if ((ring[0].x == golum.x) && (ring[0].y == golum.y))
	{
		tail++;
		golum.x = rand() % LENGTH;
		golum.y = rand() % WIDTH;
	}
	if (ring[0].x > LENGTH)
	{
		ring[0].x = 0;
	}
	if (ring[0].x < 0)
	{
		ring[0].x = LENGTH;
	}
	if (ring[0].y > WIDTH)
	{
		ring[0].y = 0;
	}
	if (ring[0].y < 0)
	{
		ring[0].y = WIDTH;
	}
	for (int i = 1; i < tail; i++)
	{
		if (ring[0].x == ring[i].x && ring[0].y == ring[i].y)
		{
			gameLost = 1;
		}
	}
}
void IsKeyPressed()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		direction = 1; // go left
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction = 2; // go right
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		direction = 3; // go up
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		direction = 0; // go down
	}
}



//main
int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(w, h), "ring lotr!");
	Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("images/lotr.png");
	t2.loadFromFile("images/ring.png");
	t3.loadFromFile("images/ring2.png");
	t4.loadFromFile("images/golum.png");
	t5.loadFromFile("images/adios.png");

	//sprites
	Sprite lotr(t1);
	Sprite ring1(t2);
	Sprite ring2(t3);
	Sprite gol(t4);
	Sprite adios(t5);


	Clock clock;
	float timer = 0, delay = 0.1;
	golum.x - 10;
	golum.y = 10;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event e;


		//closing the window with 2 different ways, and movement 
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}
					

		//check if keyispressed
		IsKeyPressed();


		if (timer > delay)
		{
			timer = 0;
			game();
		}
		window.clear();
		if (gameLost == 1)
		{
			window.draw(adios);
			window.display();
		}
		else
		{
			for (int i = 0; i < LENGTH; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					lotr.setTextureRect(IntRect(i * size, j * size, size, size));
					lotr.setPosition(i * size, j * size);
					window.draw(lotr);
				}
			}
			ring1.setPosition(ring[0].x * size, ring[0].y * size);
			window.draw(ring1);
			for (int i = 1; i < tail; i++)
			{
				ring2.setPosition(ring[i].x * size, ring[i].y * size);
				window.draw(ring2);
			}
			gol.setPosition(golum.x * size, golum.y * size);
			window.draw(gol);
			window.display();
		}
	}
	return 0;
}
