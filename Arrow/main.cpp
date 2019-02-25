#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <time.h>
#include <fstream>
#include <thread>
#include <string>
using namespace std;

bool gameOver;
const int width = 50;
const int height = 9;
const char Time = 25;
int x, y, score, Health;
int Xp = width;
int Yp = 1;
int a = 1;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN, HEND };
eDirecton dir;
HANDLE consoleHandle = 0;
std::string * Frame;

int GameOver() {
	if (gameOver == true) {
		system("cls");
		cout << "\n\n\t\tВы проиграли !" << endl;
		cout << "Набрано очков : " << score;
		Sleep(2000);
	}
	return 0;
}

void Setup() {

	HWND hwnd;
	char Title[1024];
	GetConsoleTitle(Title, 1024); // Узнаем имя окна
	hwnd = FindWindow(NULL, Title); // Узнаем hwnd окна
	MoveWindow(hwnd, 200, 100, 500, 250, TRUE);//xnew,ynew,wnew,hnew -новые положение x,y, ширина и высота
	setlocale(0, "Russian");
	srand(time(NULL));
	gameOver = false;
	Health = 100;
	score = 0;
	dir = STOP;
	x = 1;
	y = height - 3;
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	score = 0;
	
}

void LogicGame()
{
	UINT32 Speed = 400;
	while (!gameOver)
	{
		
		--Xp;
		if (Xp < 2) {
				Xp = width ;
				Yp = rand() % height;//height - 3;
				++score;
				if(Speed >= 100)
					Speed-=50;
				
		}
		if (Yp == y && Xp == x + 3) {
		
			Health -= 10; //head shot
			Xp = width;
			Yp = rand() % height;
			if (Health <= 0) {
				gameOver = true;
				GameOver();
			}
		
		}
		if (Yp == y + 1 && Xp == x + 3) {
				Health -= 5; // body shot
				Xp = width;
				Yp = rand() % height;
				if (Health <= 0) {
					gameOver = true;
					GameOver();
				}
		}
		if (Yp == y + 2 && Xp == x + 3) {
				Health -= 1; //fod shot
				Xp = width;
				Yp = rand() % height;
				if (Health <= 0) {
					gameOver = true;
					GameOver();
				}
		}
		Sleep(Speed);
	}
}

void Draw() {
	while (!gameOver)
	{
		Frame = new std::string[height + 1];
		COORD cursorCoord;
		cursorCoord.X = 0;
		cursorCoord.Y = 0;
		SetConsoleCursorPosition(consoleHandle, cursorCoord);

		for (int i = 0; i < width; i++)
			Frame[0].push_back('#');

		for (int i = 1; i < height  ; i++) {
			for (int j = 0; j < width; j++) {
				bool paintEmptyAllow = true;
				if (j == 0) { Frame[i].push_back('#'); paintEmptyAllow = false; }
				switch (dir)
				{
				case LEFT:
					if (i == y) {
						if (j == x)     { Frame[i].push_back('o'); paintEmptyAllow = false; }
						if (j == x + 1) { Frame[i].push_back('_'); paintEmptyAllow = false; }
						if (j == x + 2) { Frame[i].push_back('O'); paintEmptyAllow = false; }
					}
					if (i == y + 1) {
						if (j == x + 1) { Frame[i].push_back('/' );  paintEmptyAllow = false; }
						if (j == x + 2) { Frame[i].push_back('\f'); paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('\\'); paintEmptyAllow = false; }
					}
					if (i == y + 2) {
						if (a == 0) {
							if (j == x + 2) { Frame[i].push_back('/' );  paintEmptyAllow = false; }
							if (j == x + 3) { Frame[i].push_back('\\'); paintEmptyAllow = false; a++;}
							
						}
						else {
							if (j == x + 2) { Frame[i].push_back('|'); paintEmptyAllow = false; }
							if (j == x + 3) { Frame[i].push_back('|'); paintEmptyAllow = false; a--;}
							
						}
						
					}
					break;
				case RIGHT:
					if (i == y) {
						if (j == x + 2) { Frame[i].push_back('O');  paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('_');  paintEmptyAllow = false; }
						if (j == x + 4) { Frame[i].push_back('o');  paintEmptyAllow = false; }
					}
					if (i == y + 1) {
						if (j == x + 1) { Frame[i].push_back('/' ); paintEmptyAllow = false; }
						if (j == x + 2) { Frame[i].push_back('\f'); paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('\\'); paintEmptyAllow = false; }
					}
					if (i == y + 2) {
						if (a == 0) {
							if (j == x + 1) { Frame[i].push_back('/' );  paintEmptyAllow = false; }
							if (j == x + 2) { Frame[i].push_back('\\');  paintEmptyAllow = false; a++; }

						}
						else {
							if (j == x + 1) { Frame[i].push_back('|'); paintEmptyAllow = false; }
							if (j == x + 2) { Frame[i].push_back('|'); paintEmptyAllow = false; a--; }

						}

					}
					break;
				case UP:
					if (i == y) {
						if (j == x + 1) { Frame[i].push_back('O');   paintEmptyAllow = false; }
						if (j == x + 2) { Frame[i].push_back('_');   paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('O');   paintEmptyAllow = false; }
					}
					if (i == y + 1) {
						if (j == x + 1) { Frame[i].push_back('/' );  paintEmptyAllow = false; }
						if (j == x + 2) { Frame[i].push_back('\f');  paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('\\');  paintEmptyAllow = false; }
					}
					if (i == y + 2) {
						if (j == x + 2) { Frame[i].push_back('|');   paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('|');   paintEmptyAllow = false; }
					}
					break;
				case DOWN:
					if (i == y) {
						if (j == x )    { Frame[i].push_back('\\');  paintEmptyAllow = false; }
						if (j == x + 1) { Frame[i].push_back('O' );  paintEmptyAllow = false; }
						if (j == x + 2) { Frame[i].push_back('_' );  paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('O' );  paintEmptyAllow = false; }
						if (j == x + 4) { Frame[i].push_back('/' );  paintEmptyAllow = false; }
					}
					if (i == y + 1) {
						if (j == x + 2) { Frame[i].push_back('\f');  paintEmptyAllow = false; }
					}
					if (i == y + 2) {
						if (j == x + 2) { Frame[i].push_back('>');   paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('>');   paintEmptyAllow = false; }
					}
					break;
				case HEND:
					if (i == y) {
						if (j == x + 2) { Frame[i].push_back('O');	 paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('_');   paintEmptyAllow = false; }
						if (j == x + 4) { Frame[i].push_back('O');   paintEmptyAllow = false; }
					}
					if (i == y + 1) {
						if (j == x + 2) { Frame[i].push_back('<' );  paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('\f');  paintEmptyAllow = false; }
						if (j == x + 4) { Frame[i].push_back('>' );  paintEmptyAllow = false; }
					}
					if (i == y + 2) {
						if (j == x + 2) { Frame[i].push_back('!');   paintEmptyAllow = false; }
						if (j == x + 3) { Frame[i].push_back('!');   paintEmptyAllow = false; }
					}
					break;
				default:
					break;
				}
				if (i == Yp) {
					if (j == Xp && Xp < width - 1)	   { if ((j > x + 4 || j < x) || (i <= y || i > y + 3)) { Frame[i].push_back('<'); paintEmptyAllow = false; } }
					if (j == Xp + 1 && Xp < width - 2) { if ((j > x + 4 || j < x) || (i <= y || i > y + 3)) { Frame[i].push_back('-'); paintEmptyAllow = false; } }
					if (j == Xp + 2 && Xp < width - 3) { if ((j > x + 4 || j < x) || (i <= y || i > y + 3)) { Frame[i].push_back('-'); paintEmptyAllow = false; } }
					if (j == Xp + 3 && Xp < width - 4) { if ((j > x + 4 || j < x) || (i <= y || i > y + 3)) { Frame[i].push_back('<'); paintEmptyAllow = false; } }
					if (j == Xp + 4 && Xp < width - 5) { if ((j > x + 4 || j < x) || (i <= y || i > y + 3)) { Frame[i].push_back('<'); paintEmptyAllow = false; } }
				}
				if (j == width-1)
				{
					Frame[i].push_back('#');
					paintEmptyAllow = false;
				}
				if(paintEmptyAllow)
				{
					Frame[i].push_back(' ');
				}
			}
		}
		for (int i = 0; i < width; i++)
			Frame[height].push_back('#');

		for (size_t i = 0; i < height+1; i++) {
			printf(Frame[i].data());
			printf("\n");
		}
		

		for (int i = 0; i < width ; i++)
			printf("#");
		cout << endl;
		cout << "Score = " << score << "\n";
		cout << "Health = " << Health << "\n";
		delete[] Frame;
	}
}

void Input()
{
	while (!gameOver)
	{
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
			case 'e':
				dir = HEND;
				break;
			case 'x':
				gameOver = true;
				break;
			}
		}
	}
}

void LogicInput()
{
	while (!gameOver)
	{
		switch (dir)
		{
		case HEND:
			Sleep(Time);
			break;
		case LEFT:
			Sleep(Time);
			if (x > 1) x--;//
			if (y < height - 3) y++;
			break;
		case RIGHT:
			Sleep(Time);
			if (x < width - 6) x++;//
			if (y < height - 3) y++;
			break;
		case UP:
			Sleep(Time);
			if (y > 0) y--;
			if (y == 0) dir = DOWN;
			break;
		case DOWN:
			Sleep(Time);
			if (y < height - 3) y++;
			if (y == height - 3)dir = HEND;
			break;
		default:
			Sleep(Time);
			break;
		}
	}
}

void main()
{
	Setup();
	
	std::thread DrawThr(Draw);
	std::thread InputThr(Input);
	std::thread LogicThr(LogicInput);
	std::thread LogicGameThr(LogicGame);
	DrawThr.join();
	InputThr.join();
	LogicThr.join();
	LogicGameThr.join();
	
}