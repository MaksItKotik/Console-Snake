#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;

// Cordinate for snake
int x, y;

// Cordinate for fruits
int fruitX, fruitY;

// Cordinate for tail snake
int tailX[100], tailY[100];

// Number 0 in tail.
int nTail;

int score;

enum eDiraction { STOP = 0, LEFT, RIGHT, DOWN, UP };
eDiraction dir;

void Setup()
{
	gameOver = false;

	// On start game diraction = Stop => 0.
	dir = STOP;

	// Set started cordinate for snake.
	x = width / 2 - 1;
	y = height / 2 - 1;

	// Set random cordinate for our fruts for snake.
	fruitX = rand() % width;
	fruitY = rand() % height;

	// At start score game == 0
	score = 0;
}

void Draw()
{
	system("cls"); // <= It's command for Windows and MacOs. For Linux you must write <clear>.;


	// Top border
	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}
	cout << endl;

	// For lateral borders
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "#";
			}

			// Write position sname
			if (i == y && j == x)
			{
				cout << "0";
			}

			// Write position fruit
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}

			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}

				if (!print)
				{
					cout << " ";
				}
				
			}
			
		}
		cout << endl;
	}

	// Bottom border
	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	// Check what button is pressed.
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				dir = LEFT;
				break;

			case 'd':
				dir = RIGHT;
				break;

			case 'w':
				dir = UP;
				break;

			case 's':
				dir = DOWN;
				break;

			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}

	// Logic for press button.
	switch (dir)
	{
		case LEFT:
			x--;
			break;

		case RIGHT:
			x++;
			break;

		case DOWN:
			y++;
			break;

		case UP:
			y--;
			break;
	}


	// Teleport on X
	if (x >= width - 1)
		x = 0;

	else if (x < 0)
		x = width - 2;

	// Teleport on Y
	if (y >= width)
		y = 0;

	else if (y < 0)
		y = width - 1;

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		// Score += 10;
		score += 10;

		// Set new position for fruit.
		fruitX = rand() % width;
		fruitY = rand() % height;

		nTail++;
	}
}

int main()
{
	Setup();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic();

		Sleep(50);
	}

	return 0;
}