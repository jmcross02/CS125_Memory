//Jackson Cross
//#include "TextDraw.h"
//#include "MyRectangle.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include "Coordinates.h"
#include "MyMouse.h"
#include "MySound.h"
#include "stdlib.h"

using namespace std;
//first we need to set up our functions, starting with the position function
void gotoPOS(int x, int y)
{
	COORD P;
	P.X = x;
	P.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), P);
}
//then we need to load in our data from files
void loadCard(string filename, int arr[15][15])
{
	int i;
	ifstream input(filename);
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			input >> arr[i][j];
}
//finally we need to set up a function to display our card
void cardReader(int values[15][15], int colors[15][15], int x, int y)
{
	gotoPOS(x, y);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			SetConsoleTextAttribute(hConsole, colors[i][j]);
			gotoPOS(x + j, y + i);
			cout << char(values[i][j]);

		}
		cout << endl;
	}

}
//we need a function linking click locations to corresponding card numbers
int CardNum(int x, int y)
{
	if ((x >= 1 && x <= 15) && (y >= 1 && y <= 15))
		return 1;

	if ((x >= 17 && x <= 32) && (y >= 1 && y <= 15))
		return 2;

	if ((x >= 33 && x <= 48) && (y >= 1 && y <= 15))
		return 3;

	if ((x >= 49 && x <= 64) && (y >= 1 && y <= 15))
		return 4;

	if ((x >= 1 && x <= 15) && (y >= 17 && y <= 32))
		return 5;

	if ((x >= 17 && x <= 32) && (y >= 17 && y <= 32))
		return 6;

	if ((x >= 33 && x <= 48) && (y >= 17 && y <= 32))
		return 7;

	if ((x >= 49 && x <= 64) && (y >= 17 && y <= 32))
		return 8;

	if ((x >= 1 && x <= 15) && (y >= 33 && y <= 48))
		return 9;

	if ((x >= 17 && x <= 32) && (y >= 33 && y <= 48))
		return 10;

	if ((x >= 33 && x <= 48) && (y >= 33 && y <= 48))
		return 11;

	if ((x >= 49 && x <= 64) && (y >= 33 && y <= 48))
		return 12;
	return 0;
}
//we then need to link card numbers to x y coordinates in which to display the card
void DisplayPick(int cardNumber, int card[15][15], int color[15][15])
{
	int x = -1;
	int y = -1;
	if (cardNumber == 1)
	{
		x = 1;
		y = 1;
	}
	if (cardNumber == 2)
	{
		x = 17;
		y = 1;
	}
	if (cardNumber == 3)
	{
		x = 33;
		y = 1;
	}
	if (cardNumber == 4)
	{
		x = 49;
		y = 1;
	}
	if (cardNumber == 5)
	{
		x = 1;
		y = 17;
	}
	if (cardNumber == 6)
	{
		x = 17;
		y = 17;
	}
	if (cardNumber == 7)
	{
		x = 33;
		y = 17;
	}
	if (cardNumber == 8)
	{
		x = 49;
		y = 17;
	}
	if (cardNumber == 9)
	{
		x = 1;
		y = 33;
	}
	if (cardNumber == 10)
	{
		x = 17;
		y = 33;
	}
	if (cardNumber == 11)
	{
		x = 33;
		y = 33;
	}
	if (cardNumber == 12)
	{
		x = 49;
		y = 33;
	}
	if ((x > -1) && (y > -1));
	cardReader(card, color, x, y);
}
void main()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 12;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_BOLD;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	SetConsoleTitleA("MEMORY V9");

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	MyMouse M;
	MySound S;
	//initializing card arrays
	int arr[13][15][15];
	int arr_colors[13][15][15];

	gotoPOS(70, 5);
	cout << "Welcome to Memory! This is a twelve card version of the game. Click on a card to reveal it. Match all six pairs to win!";
	gotoPOS(70, 7);
	cout << "WARNING: PLEASE TAKE AT LEAST TEN SECONDS BETWEEN CLICKS TO PERMIT THE SYSTEM TO BUFFER. PEASE LOWER YOUR VOLUME FOR GAME SOUNDS.";
	gotoPOS(70, 20);
	cout << "Moves:";
	gotoPOS(68, 25);
	cout << "Matches:";
	//setting up our initial display of flipped cards
	loadCard("files/card_blank.txt", arr[0]);
	loadCard("files/card_blank_colors.txt", arr_colors[0]);

	cardReader(arr[0], arr_colors[0], 1, 1);
	cardReader(arr[0], arr_colors[0], 17, 1);
	cardReader(arr[0], arr_colors[0], 33, 1);
	cardReader(arr[0], arr_colors[0], 49, 1);
	cardReader(arr[0], arr_colors[0], 1, 17);
	cardReader(arr[0], arr_colors[0], 17, 17);
	cardReader(arr[0], arr_colors[0], 33, 17);
	cardReader(arr[0], arr_colors[0], 49, 17);
	cardReader(arr[0], arr_colors[0], 1, 33);
	cardReader(arr[0], arr_colors[0], 17, 33);
	cardReader(arr[0], arr_colors[0], 33, 33);
	cardReader(arr[0], arr_colors[0], 49, 33);



	int numPicked = 0;
	int cardValues[12] = { 1, 4, 7, 3, 5, 2, 1, 4, 7, 3, 5, 2 };
	int blankCard[15][15];
	int blankCard_colors[15][15];
	//back

	//card 1

	loadCard("files/card1.txt", arr[1]);
	loadCard("files/card1colors.txt", arr_colors[1]);

	loadCard("files/card1.txt", arr[7]);
	loadCard("files/card1colors.txt", arr_colors[7]);


	//card 2

	loadCard("files/card2.txt", arr[2]);
	loadCard("files/card2colors.txt", arr_colors[2]);
	loadCard("files/card2.txt", arr[8]);
	loadCard("files/card2colors.txt", arr_colors[8]);

	//card 3

	loadCard("files/card3.txt", arr[3]);
	loadCard("files/card3colors.txt", arr_colors[3]);
	loadCard("files/card3.txt", arr[9]);
	loadCard("files/card3colors.txt", arr_colors[9]);

	//card 4

	loadCard("files/card7.txt", arr[4]);
	loadCard("files/card7colors.txt", arr_colors[4]);
	loadCard("files/card7.txt", arr[10]);
	loadCard("files/card7colors.txt", arr_colors[10]);


	//card 5

	loadCard("files/card5.txt", arr[5]);
	loadCard("files/card5colors.txt", arr_colors[5]);
	loadCard("files/card5.txt", arr[11]);
	loadCard("files/card5colors.txt", arr_colors[11]);


	//card 6

	loadCard("files/card6.txt", arr[6]);
	loadCard("files/card6colors.txt", arr_colors[6]);
	loadCard("files/card6.txt", arr[12]);
	loadCard("files/card6colors.txt", arr_colors[12]);

	//need to load a blank card for successful matches
	loadCard("files/blankcard.txt", blankCard);
	loadCard("files/blankcard_colors.txt", blankCard_colors);

	//need to add a method to count the number of clicks
	int clickCount = 0;
	//a counter for the number of moves
	int moveCount = 0;
	//and the number of successful pairs
	int matches = 0;
	//setting up move and match counters
	gotoPOS(78, 20);
	cout << moveCount;
	gotoPOS(78, 25);
	cout << matches;
	//setting up variables for flipping and matching cards.
	int firstValue;
	int secondValue;
	int firstCard;
	int secondCard;

	while (1)
	{
		/*I added the console input buffer however my code still suffers from problems if the user doesn't wait between clicks.
		I am unsure what the source of this problem could be because the code doesn't seem to have any errors.*/
		FlushConsoleInputBuffer(GetConsoleWindow());
		M.ReadMouseInput();
		switch (M.InputRecord.EventType)
		{
		case MOUSE_EVENT:
			if (M.InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				int x = M.InputRecord.Event.MouseEvent.dwMousePosition.X;
				int y = M.InputRecord.Event.MouseEvent.dwMousePosition.Y;
				int CardPick = CardNum(x, y);
				//eliminate clicks that aren't even on the cards.
				if (CardPick == 0)
				{
					gotoPOS(90, 20);
					cout << "Invalid input, please try again.";
				}
				//make sure the coordinates clicked return the correct variable
				else if ((cardValues[CardPick] != 99) && (CardPick != 0))
				{
					DisplayPick(CardPick, arr[CardPick], arr_colors[CardPick]);
					if (clickCount == 0)
					{
						firstValue = cardValues[CardPick - 1];
						clickCount = 1;
						firstCard = CardPick;
					}
					else
					{
						secondValue = cardValues[CardPick - 1];
						clickCount = 0;
						secondCard = CardPick;
						moveCount = moveCount + 1;

						gotoPOS(78, 20);
						cout << moveCount;

						if (firstValue == secondValue)
						{
							//play a sound for a match
							S.Play(L"files/Win.wav", NULL, SND_LOOP);
							//update score count and scoreboard
							matches = matches + 1;
							gotoPOS(78, 25);
							cout << matches;
							//eliminate successfully matched cards
							cardValues[firstCard] = 99;
							cardValues[secondCard] = 99;

							DisplayPick(firstCard, blankCard, blankCard_colors);
							DisplayPick(secondCard, blankCard, blankCard_colors);

						}
						else
						{
							//play a sound for incorrect pairing.
							S.Play(L"files/Brainrot.wav", NULL, SND_LOOP);
							Sleep(500);
							//reset mismatched cards.
							DisplayPick(firstCard, arr[0], arr_colors[0]);
							DisplayPick(secondCard, arr[0], arr_colors[0]);

						}

					}
				}
				//a way to notify players that they have won the game
				if (matches == 6)
				{
					S.Play(L"files/BigWin.wav", NULL, SND_LOOP);
					system("cls");
					break;
					matches == 0;
					//I was unable to get the victory message to print regardless of the presence of break and cls. I am not sure what I did wrong.
					gotoPOS(70, 50);
					cout << "YOU WON!";
				}
				//next a sound file to encourage struggling players
				if (moveCount == 15)
				{
					S.Play(L"files/Encouragement.wav", NULL, SND_LOOP);
				}

			}
			break;
		}

	}
}

