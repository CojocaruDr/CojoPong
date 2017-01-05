#include "MenuFunctions.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <sstream>
using namespace std;
ifstream scoreBoard("Scores.txt");



struct highscore
{
	char player1[21];
	char player2[21];
	int P1_Score, P2_Score;
	highscore *next;
};

void HS_add(highscore* &board, char playerOne[21], char playerTwo[21], int scoreOne, int scoreTwo)
{
	highscore *p = board;
	if (board == NULL)
	{
		board = new highscore;
		board->P1_Score = scoreOne;
		board->P2_Score = scoreTwo;
		strcpy_s(board->player1, playerOne);
		strcpy_s(board->player2, playerTwo);
		board->next = NULL;

	}
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = new highscore;
		p = p->next;
		p->P1_Score = scoreOne;
		p->P2_Score = scoreTwo;
		strcpy_s(p->player1, playerOne);
		strcpy_s(p->player2, playerTwo);
		p->next = NULL;
	}
	
}

void afisareLista(highscore* list)
{
	highscore *p = list;
	while (p != NULL)
	{
		cout << p->P1_Score << "     " << p->player1 << "      " << p->player2 << "    " << p->P2_Score << endl;
		p = p->next;
	}
	delete p;
}

highscore *HS_Update()
{
	int scoreOne=0, scoreTwo=0;
	highscore *board = NULL;
	char playerOne[21], playerTwo[21];

	while (scoreOne != -1)
	{
		scoreBoard >> scoreOne;
		if (scoreOne == -1)
			break;
		else
		{
			scoreBoard.get();
			scoreBoard.getline(playerOne, 21);

			scoreBoard.getline(playerTwo, 21);

			scoreBoard >> scoreTwo;

			scoreBoard.get();
			HS_add(board, playerOne,playerTwo,scoreOne,scoreTwo);
		}
	} 
	scoreBoard.clear();
	scoreBoard.seekg(0, scoreBoard.beg);
	return board;
}

std::string intToString(int number)
{
	std::string result;
	ostringstream convert;
	convert << number;
	result = convert.str();
	return result;
}

void displayHistory(highscore* &list)
{
	int currentX = 135, currentY = 230;
	std::string currentText;

	while (list)
	{
		currentText = intToString(list->P1_Score);

		loadText(currentText);
		textTexture.render(currentX, currentY);
		currentX += 230;

		loadText(list->player1);
		textTexture.render(currentX, currentY);
		currentX += 350;

		loadText(list->player2);
		textTexture.render(currentX, currentY);

		currentX += 300;
		currentText = intToString(list->P2_Score);

		loadText(currentText);
		textTexture.render(currentX, currentY);

		currentY += 50;
		currentX -= 880;
		list = list->next;
	}
}

void openScores()
{
	highscore *HS_list = NULL;
	SDL_RenderClear(gRenderer);
	SDL_RenderSetViewport(gRenderer, NULL);
	loadMedia("Resources/Scores_BG.bmp");
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	SDL_RenderPresent(gRenderer);
	HS_list = HS_Update();

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	displayHistory(HS_list);

	SDL_RenderPresent(gRenderer);
}