#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

// Define keyboard inputs
#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_LEFT 75

// Game global variables
bool gameover;
const int mapWidth = 100;
const int mapHeight = 20;
int snakeHeadX, snakeHeadY, fruitX, fruitY, score;
const int mapSize = mapWidth * mapHeight;
const int walls = 2 * mapWidth + 2 * (mapHeight - 2);
const int maxSnakeTails = mapSize - walls;
int snakeTailX[maxSnakeTails], snakeTailY[maxSnakeTails], snakeTailsCount;
enum class Direction { STOP = 0, UP, RIGHT, DOWN, LEFT };
Direction dir;

// Start the game
void Start() {
	gameover = false;
	// Center the head of the snake in the map
	snakeHeadX = mapWidth / 2;
	snakeHeadY = mapHeight / 2;
	// Random fruits in the map
	fruitX = rand() % mapWidth;
	fruitY = rand() % mapHeight;
	// Init tails
	snakeTailsCount = 2;
	snakeTailX[0] = snakeHeadX - 1;
	snakeTailY[0] = snakeHeadY;
	snakeTailX[1] = snakeHeadX - 2;
	snakeTailY[1] = snakeHeadY;
}

// Render walls (#), snake (ooooO) and fruits (*)
void Render() {
	system("cls");
	for (int i = 1; i <= mapHeight; i++) {
		for (int j = 1; j <= mapWidth; j++)
			if (i == 1 || j == 1 || i == mapHeight || j == mapWidth)
				cout << "#";
			else if (i == snakeHeadY && j == snakeHeadX)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "*";
			else {
				bool isSnakeTail = false;
				for (int k = 0; k < snakeTailsCount; k++)
					if (i == snakeTailY[k] && j == snakeTailX[k])
						isSnakeTail = true;
				if (isSnakeTail)
					cout << "o";
				else
					cout << " ";
			}
		cout << endl;
	}
	Sleep(100);
}

// Handle inputs
void Input() {
	if (_kbhit()) {
		int key = _getch();
		switch (key) {
		case KEY_UP:
			dir = Direction::UP;
			break;
		case KEY_RIGHT:
			dir = Direction::RIGHT;
			break;
		case KEY_DOWN:
			dir = Direction::DOWN;
			break;
		case KEY_LEFT:
			dir = Direction::LEFT;
			break;
		default:
			break;
		}
	}
}

// Game logic
int prevX, prevY, prev2X, prev2Y;
void Logic() {
	if (dir != Direction::STOP) {
		prevX = snakeTailX[0];
		prevY = snakeTailY[0];
		snakeTailX[0] = snakeHeadX;
		snakeTailY[0] = snakeHeadY;
		for (int i = 1; i < snakeTailsCount; ++i) {
			prev2X = snakeTailX[i];
			prev2Y = snakeTailY[i];
			snakeTailX[i] = prevX;
			snakeTailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
	}
	switch (dir) {
	case Direction::UP:
		snakeHeadY--;
		break;
	case Direction::RIGHT:
		snakeHeadX++;
		break;
	case Direction::DOWN:
		snakeHeadY++;
		break;
	case Direction::LEFT:
		snakeHeadX--;
		break;
	default:
		break;
	}
	if (snakeHeadX > mapWidth) snakeHeadX = 0;
	else if (snakeHeadX < 0) snakeHeadX = mapWidth;
	if (snakeHeadY > mapHeight) snakeHeadY = 0;
	else if (snakeHeadY < 0) snakeHeadY = mapHeight;
}

// Update the game
void Update() {
	while (!gameover) {
		Render();
		Input();
		Logic();
	}
}

void main() {
	Start();
	Update();
}