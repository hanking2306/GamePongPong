#include<iostream>
#include<time.h>
#include<conio.h>

using namespace std;

enum  eDirection {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class Ball {
private:
	int x, y;
	int originalX, originalY;
	eDirection dir;
public:
	Ball(int posX, int posY) {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		dir = STOP;
	}
	void Reset() {
		x = originalX;
		y = originalY;
		dir = STOP;
	}
	void changeDirection(eDirection d) {
		dir = d;
	}
	void randomDirection() {
		srand(time(NULL));
		dir = (eDirection)((rand() % 6) + 1);
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDirection getDirection() { return dir; }
	void Move() {
		switch (dir)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case RIGHT:
			x++;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		default:
			break;
		}
	}
};

class Paddle {
private:
	int x, y;
	int originalX, originalY;
public:
	Paddle() {
		x = y = 0;
	}
	Paddle(int posX, int posY) : Paddle() {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset() {
		x = originalX;
		y = originalY;
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline int moveUp() { return y--; }
	inline int moveDown() { return y++; }
};

class GameManager {
private:
	int width, height;
	char up1, down1, up2, down2;
	bool quit;
	Ball *ball;
	Paddle *player1;
	Paddle *player2;
public:
	GameManager(int width, int height) {
		this -> width = width;
		this -> height = height;
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = '8';
		down1 = 's'; down2 = '5';
		ball = new Ball(width / 2, height / 2);
		player1 = new Paddle(1, height / 2 - 3);
		player2 = new Paddle(width - 2, height / 2 - 3);
	}
	void Draw() {
		system("cls");
		cout << "\t\t\t\t";
		for (int i = 0; i < width + 2; i++)
			cout << "\xDB";
		cout << endl;
		for (int i = 0; i < height; i++){
			cout << "\t\t\t\t";
			for (int j = 0; j < width; j++){
				int ballX = ball->getX();
				int ballY = ball->getY();
				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();

				if (j == 0)
					cout << "\xDB";
				if (j == ballX && i == ballY)
					cout << "\xE9";
				else if (j == player1x && i == player1y)
					cout << "\xDB";
				else if (j == player1x && i == player1y + 1)
					cout << "\xDB";
				else if (j == player1x && i == player1y + 2)
					cout << "\xDB";
				else if (j == player1x && i == player1y + 3)
					cout << "\xDB";
				else if (j == player2x && i == player2y)
					cout << "\xDB";
				else if (j == player2x && i == player2y + 1)
					cout << "\xDB";
				else if (j == player2x && i == player2y + 2)
					cout << "\xDB";
				else if (j == player2x && i == player2y + 3)
					cout << "\xDB";
				else cout << " ";
				if (j == width - 1)
					cout << "\xDB";
			}
			cout << endl;
		}
		cout << "\t\t\t\t";
		for (int i = 0; i < width + 2; i++)
			cout << "\xDB";
		cout << endl;
	}
	void Input() {
		ball->Move();
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();
		if (_kbhit()) {
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					player1->moveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();
			if (current == up2)
				if (player2y > 0)
					player2->moveUp();
			if (current == down2)
				if (player2y + 4 < height)
					player2->moveDown();
			if (ball->getDirection() == STOP)
				ball->randomDirection();
			if (current == 'x')
				quit = true;
		}
	}
	void Logic() {
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();
		for (int i = 0; i < 4; i++)
			if (ballX == player1x + 1)
				if (ballY == player1y + i)
					ball->changeDirection(eDirection((rand() % 3) + 4));
		for (int i = 0; i < 4; i++)
			if (ballX == player2x - 1)
				if (ballY == player2y + i)
					ball->changeDirection(eDirection((rand() % 3) + 1));
		if (ballY == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		if (ballY == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		if (ballX == 0) {
			quit = true;
			cout << " Player 2 WIN";
		}
		if (ballX == width - 1) {
			quit = true;
			cout << " Player 1 WIN";
		}
	}
	void Run() {
		while (!quit){
			Draw();
			Input();
			Logic();
		}
	}
};

int main() {
	GameManager game(50, 20);
	game.Run();
	return 0;
}