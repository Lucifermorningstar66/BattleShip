#include <iostream>
#include <time.h>
#include <string>
#include <math.h>
#include <conio.h>
#include <chrono>

using namespace std;

auto start = chrono::system_clock::now();

int n;
char** board; //dynamic
int playerTrueAttack;
int playerWrongAttack;
int systemTrueAttack;
int systemWrongAttack;
int playerSurvivrdShip;
int systemSurvivedShip;
bool win, tied;


void input() {
	cin >> n;
}


void setBoard() {
	board = new char* [n];  //pointer to char
	for (int i = 0; i < n; i++) {
		board[i] = new char[n - 1];  
		for (int j = 0; j < n - 1; j++) {
			board[i][j] = '#';
		}
	}
}

void printCell(char cell) {
	cout << cell << " ";  //char for printing
}

void printBoard() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (j == n / 2) {
				printCell('|');
			}
			printCell(board[i][j]);
		}
		cout << endl;
	}
}

double calculateScore()
{
	return (((double)n / (playerWrongAttack + 1)) + playerTrueAttack + playerSurvivrdShip);  
}

void topPannel()
{
	cout << "[======Welcome To BATTLESHIP======]\n";

}

void bottomPannel()
{
	cout << "SCORE:" << calculateScore() << endl;;
}

void setGlobals()
{
	playerTrueAttack = 0;
	playerWrongAttack = 0;
	systemTrueAttack = 0;
	systemWrongAttack = 0;
	playerSurvivrdShip = n;
	systemSurvivedShip = n;
	win = false;
	tied = false;
}


void render()
{
	system("CLS");
	topPannel();
	printBoard();
	bottomPannel();

	auto end = chrono::system_clock::now();

	chrono::duration<double> time = (end - start);
	int all = (int)time.count();
	int sec = all % 60;
	int min = (all % 3600) / 60;
	int hour = all / 3600;

	cout << hour << ":" << min << ":" << sec << endl;
}


void playerAttack() {
	int x, y;
	do {
		render();
		cout << "Attack(column,row): ";
		cin >> y >> x;
	} while (x < n / 2 || x >= n || y >= n || y < 0 || board[y][x] == '1' || board[y][x] == '0');

	if (board[y][x] == '*') {
		board[y][x] = '1';
		playerTrueAttack++;
		systemSurvivedShip--;
	}
	else {
		board[y][x] = '0';
		playerWrongAttack++;
	}
}


void systemAttack() {
	int x, y;
	do
	{
		srand(time(NULL));
		x = rand() % (n / 2);
		y = rand() % n;
	} while (board[y][x] == '1' || board[y][x] == '0');


	if (board[y][x] == '*')
	{
		board[y][x] = '1';
		systemTrueAttack++;
		playerSurvivrdShip--;
	}
	else {
		board[y][x] = '0';
		systemWrongAttack++;
	}
}


void playerSet() {
	int x, y;
	do {
		render();
		cout << "Set(column,row):";
		cin >> y >> x;
	} while (x >= n / 2 || x < 0 || y >= n || y < 0 || board[y][x] == '*');

	board[y][x] = '*';
}


void systemSet() {
	int x, y;
	do {
		srand(time(NULL));
		x = rand() % (n / 2) + (n / 2);
		y = rand() % n;
	} while (board[y][x] == '*');

	board[y][x] = '*';
}


void gameLoop() {
	for (int i = 0; i < n; i++)
	{
		playerSet();
		systemSet();
		render();
	}
	bool gameOver = false;

	while (!gameOver)
	{
		playerAttack();
		systemAttack();
		render();

		if (playerSurvivrdShip == 0 && systemSurvivedShip == 0) {
			gameOver = true;
			tied = true;
		}
		else if (playerSurvivrdShip == 0) {
			gameOver = true;
		}
		else if (systemSurvivedShip == 0) {
			gameOver = true;
			win = true;
		}
	}
}


void playGame() {
	input();
	setGlobals();
	setBoard();
	render();
	gameLoop();
	if (win) {
		cout << "You Won...";
	}
	else if (tied) {
		cout << "Tied...";
	}
	else {
		cout << "You Lost...";
	}
}


int main()
{
	playGame();
	return 0;
}