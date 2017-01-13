#include "MenuFunctions.h"
struct highscore
{
	char player1[21];
	char player2[21];
	int P1_Score, P2_Score;
	highscore *next;
	highscore *pred;
};

void HS_add(highscore* &board, char playerOne[21], char playerTwo[21], int scoreOne, int scoreTwo)
{
	highscore *p = board, *lastHS = board;
	if (board == NULL)
	{
		board = new highscore;
		board->P1_Score = scoreOne;
		board->P2_Score = scoreTwo;
		strcpy_s(board->player1, playerOne);
		strcpy_s(board->player2, playerTwo);
		board->next = NULL;
		board->pred = NULL;

	}
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
			p->pred = lastHS;
			lastHS = lastHS->next;
		}
		p->next = new highscore;
		p = p->next;
		p->P1_Score = scoreOne;
		p->P2_Score = scoreTwo;
		strcpy_s(p->player1, playerOne);
		strcpy_s(p->player2, playerTwo);
		p->pred = lastHS;
		p->next = NULL;
	}

}

int lineToInt(std::string line)
{
	if (line[0] <= '9'&& line[0] >= '0')
	{
		return atoi(&line[0]);
	}
	else return -1;
}

highscore *HS_Update()
{
	int scoreOne = 0, scoreTwo = 0;
	std::string line;
	highscore *board = NULL;
	char playerOne[21], playerTwo[21];
	scoreBoard.open("Scores.txt");
	scoreBoard.get();
	if (scoreBoard.peek() == std::ifstream::traits_type::eof())
	{
		return NULL;
	}

	while (!scoreBoard.eof())
	{
		getline(scoreBoard, line);
		scoreOne = lineToInt(line);
		if (scoreOne == -1)
			break;
		scoreBoard.getline(playerOne, 21);

		scoreBoard.getline(playerTwo, 21);

		scoreBoard >> scoreTwo;

		scoreBoard.get();
		scoreBoard.get();
		HS_add(board, playerOne, playerTwo, scoreOne, scoreTwo);
	}

	scoreBoard.clear();
	scoreBoard.seekg(0, scoreBoard.beg);
	scoreBoard.close();
	while (board->next)
	{
		board = board->next;
	}
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
	int Nr_Intrari = 9;
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
		list = list->pred;
		Nr_Intrari--;
		if (Nr_Intrari == 0)
			break;
	}
}

void openScores()
{
	highscore *HS_list = NULL;
	SDL_RenderClear(gRenderer);
	SDL_RenderSetViewport(gRenderer, NULL);
	loadMedia("Resources/HighScore_BG.bmp");
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	SDL_RenderPresent(gRenderer);
	HS_list = HS_Update();


	displayHistory(HS_list);

	SDL_RenderPresent(gRenderer);
}