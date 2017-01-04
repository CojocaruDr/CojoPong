#include "MenuFunctions.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
using namespace std;
ifstream scoreBoard("Scores.txt");

struct highscore
{
	char userName[21];
	int score;
	highscore *next;
};

void HS_add (highscore* board, char user[21], int score)
{
	

}

void HS_Update()
{
	int number = 0;
	highscore *board = NULL;
	//while (number != -1)
	//{
		scoreBoard >> number;
		cout << number << endl;
		scoreBoard.get();
		
		cout << number;
	//}
}

void openScores()
{
	SDL_RenderClear(gRenderer);
	SDL_RenderSetViewport(gRenderer, NULL);
	loadMedia("Resources/Scores_BG.bmp");
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	SDL_RenderPresent(gRenderer);
	HS_Update();
}