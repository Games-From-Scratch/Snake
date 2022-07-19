#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

// Game global variables
bool gameover;
const int mapWidth = 100;
const int mapHeight = 20;
int snakeHeadX, snakeHeadY, fruitX, fruitY, score;
const int mapSize = mapWidth * mapHeight;
const int walls = 2 * mapWidth + 2 * (mapHeight - 2);
const int maxSnakeTails = mapSize - walls;
int snakeTailX[maxSnakeTails], snakeTailY[maxSnakeTails], snakeTailsCount;

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

// Update the game
void Update() {
	while (!gameover) {
		Render();
	}
}

void main() {
	Start();
	Update();
}