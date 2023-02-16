#include <iostream>
#include <random>
#include <conio.h>
using namespace std;

bool setApple(char** field)
{
	return 1;
}

struct snakePart
{
	int x, y;
	snakePart* next;
	snakePart* prev;
};

void printField(char** field, int fieldHeight, int fieldWhidth)
{
	for (int i = 0; i < fieldHeight; i++)
	{
		for (int j = 0; j < fieldWhidth; j++)
		{
			cout << field[i][j];
		}
		cout << "|\n";
	}
	for (int j = 0; j < fieldWhidth; j++)
	{
		cout << "-";
	}
	cout << "+";
}

void clearField(char** field, int fieldHeight, int fieldWhidth)
{
	for (int i = 0; i < fieldHeight; i++)
	{
		for (int j = 0; j < fieldWhidth; j++)
		{
			field[i][j] = ' ';
		}
	}
}



int main()
{
	setlocale(LC_ALL, "ru");
	int fieldWhidth, fieldHeight;
	do
	{
		system("cls");
		cout << "Введите ширину поля: ";
		cin >> fieldWhidth;
		cout << "Введите высоту поля: ";
		cin >> fieldHeight;

	} while ((fieldWhidth <= 2) or (fieldHeight <= 2));

	char** field = new char* [fieldHeight];
	//Создаем поля
	for (int i = 0; i < fieldHeight; i++)
	{
		field[i] = new char[fieldWhidth];
	}
	////Опустощаем поля
	clearField(field, fieldHeight, fieldWhidth);

	system("cls");
	for (int i = 0; i < fieldHeight; i++)
	{
		for (int j = 0; j < fieldWhidth; j++)
		{
			cout << field[i][j];
		}
		cout << endl;
	}
	//Инициализируем змейку
	snakePart snake;
	snakePart* snakeHead = &snake;

	//Ставим голову змейку в случайный место
	snake.x = rand() % fieldWhidth;
	snake.y = rand() % fieldHeight;
	snake.next = NULL;
	snake.prev = NULL;

	bool alive = true;
	char symbol;//Считываемые символ с клавиатура
	int currentLength = 0;

	int appleX, appleY;
	appleX = rand() % fieldWhidth;
	appleY = rand() % fieldHeight;

	snakePart* snakeCurrent = snakeHead;
	//snakePart* snakeTail = snakeHead;
	
	int snakeXprev, snakeYprev;
	int length = 1;
	while (alive)
	{
		snakeXprev = snake.x;
		snakeYprev = snake.y;
		symbol = _getch();
		if ((symbol == 'w') or (symbol == 'W'))
		{
			snake.y -= 1;
			if (snake.y < 0) snake.y = fieldHeight - 1;
		}
		if ((symbol == 's') or (symbol == 'S'))
		{
			snake.y = (snake.y + 1) % fieldHeight;
		}
		if ((symbol == 'a') or (symbol == 'A'))
		{
			snake.x -= 1;
			if (snake.x < 0) snake.x = fieldWhidth - 1;
		}
		if ((symbol == 'd') or (symbol == 'D'))
		{
			snake.x = (snake.x + 1) % fieldWhidth;
		}

		snakeCurrent = snakeHead;
		if (length > 1)
		{
			snakeCurrent = snakeCurrent-> next;
			while (snakeCurrent->next != NULL)
			{
				if (field[snake.y][snake.x] == '@')
				{
					alive = false;
					break;
				}
				snakeCurrent = snakeCurrent->next;
			}
		}

		if ((snake.x == appleX) and (snake.y == appleY))
		{
			do
			{
				appleX = rand() % fieldWhidth;
				appleY = rand() % fieldHeight;

			} while (field[appleY][appleX] != ' ');

			snakeCurrent = snakeHead;

			while (snakeCurrent->next != NULL) snakeCurrent = snakeCurrent->next;
			snakeCurrent->next = new snakePart;
			snakeCurrent->next->x = snakeXprev;
			snakeCurrent->next->y = snakeYprev;
			snakeCurrent->next->prev = snakeCurrent;
			snakeCurrent->next->next = NULL;
			length++;
		}

		snakeCurrent = snakeHead;
		if (length > 1)
		{
			while (snakeCurrent->next != NULL) snakeCurrent = snakeCurrent->next;
			while (snakeCurrent != snakeHead->next)
			{
				snakeCurrent->x = snakeCurrent->prev->x;
				snakeCurrent->y = snakeCurrent->prev->y;

				snakeCurrent = snakeCurrent->prev;
			}
			snakeCurrent->x = snakeXprev;
			snakeCurrent->y = snakeYprev;
		}

		snakeCurrent = snakeHead;
		currentLength = 0;
		clearField(field, fieldHeight, fieldWhidth);

		field[appleY][appleX] = '+';

		while (snakeCurrent != NULL)
		{
			if(currentLength == 0) field[snakeCurrent->y][snakeCurrent->x] = 'O';
			else field[snakeCurrent->y][snakeCurrent->x] = '@';
			currentLength++;
			snakeCurrent = snakeCurrent->next;
		}
		system("cls");

		cout << "You current score: " << length << endl;
		printField(field, fieldHeight, fieldWhidth);
	}

	cout << "\nGame over! You Score: " << length << endl;
}  