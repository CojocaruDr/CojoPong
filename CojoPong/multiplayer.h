#include <ctime>
#include "MenuFunctions.h"
#include <sstream>
//e o problema in applyBuffs();
const int ball_x = 580;
const int ball_y = 390;
const int obstacle_x = 545;
const int obstacle_y = 21;
int xDir, yDir,obstacleDir=5,scoreOneCounter=0,scoreTwoCounter=0,maxPoints;
std::string scoreOne="0",scoreTwo="0";
bool gameStart = false;
bool GAME = true;
bool gameOver = false;
bool powerHit = false;
bool buffApplied = false;
bool speedOn = false;
int lastHit;
int sizeApplied = 0;

void resetGame();
void SetupRenderer();
void Render();
void RunMultiPlayerGame();
void resetBall();
int getRandomNumber(int high, int low);

SDL_Rect pOnePaddle;
SDL_Rect pTwoPaddle;
SDL_Rect ball;
SDL_Rect obstacle;
SDL_Rect powerUp;

struct paddleSize {
	int sizeIncrease;
	int segOneIncrease;
	int segTwoIncrease;
	int segThreeIncrease;
	int segFourIncrease;
	int segFiveIncrease;
	int segSixIncrease;
	int segSevenIncrease;
	int segEightIncrease;
	int segNineIncrease;
	int segTenIncrease;
	int segElevenIncrease;
	int segTwelveIncrease;
	int segThirteenIncrease;
	int segFourteenIncrease;
	int segFifteenIncrease;
	int segSixteenIncrease;
}paddleBuff;

struct node {
	int value;
	node* next;
};
node *head=NULL;

void addPowerUp(node* &head, int value)
{
	node *p = head;
	if (!head)
	{
		head = new node;
		head->value = value;
		head->next = NULL;
	}
	else
	{
		while (p->next)
		{
			p = p->next;
		}
		p->next = new node;
		p = p->next;
		p->value = value;
		p->next = NULL;
	}

}

void createPowerUpsQueue(node* &head)
{
	for (int position = 0; position < 19; position++)
	{
		addPowerUp(head, getRandomNumber(3,1));
	}
}

void setSegSize()
{
	paddleBuff.sizeIncrease = 48;
	paddleBuff.segOneIncrease = 3;
	paddleBuff.segTwoIncrease = 6;
	paddleBuff.segThreeIncrease = 9;
	paddleBuff.segFourIncrease = 12;
	paddleBuff.segFiveIncrease = 15;
	paddleBuff.segSixIncrease = 18;
	paddleBuff.segSevenIncrease = 21;
	paddleBuff.segEightIncrease = 24;
	paddleBuff.segNineIncrease = 27;
	paddleBuff.segTenIncrease = 30;
	paddleBuff.segElevenIncrease = 33;
	paddleBuff.segTwelveIncrease = 36;
	paddleBuff.segThirteenIncrease = 39;
	paddleBuff.segFourteenIncrease = 42;
	paddleBuff.segFifteenIncrease = 45;
	paddleBuff.segSixteenIncrease = 48;
}
void setSegSizeNot()
{
	paddleBuff.segOneIncrease = 0;
	paddleBuff.segTwoIncrease = 0;
	paddleBuff.segThreeIncrease = 0;
	paddleBuff.segFourIncrease = 0;
	paddleBuff.segFiveIncrease = 0;
	paddleBuff.segSixIncrease = 0;
	paddleBuff.segSevenIncrease = 0;
	paddleBuff.segEightIncrease = 0;

	paddleBuff.segNineIncrease = 0;
	paddleBuff.segTenIncrease = 0;
	paddleBuff.segElevenIncrease = 0;
	paddleBuff.segTwelveIncrease = 0;
	paddleBuff.segThirteenIncrease = 0;
	paddleBuff.segFourteenIncrease = 0;
	paddleBuff.segFifteenIncrease = 0;
	paddleBuff.segSixteenIncrease = 0;
}
void multiPlayer()
{
	lastHit = 3;

	if (toggle.points)
		maxPoints = 5;
	else
		maxPoints = 10;

	if (toggle.powerUpsOn)
	{
		createPowerUpsQueue(head);
		setSegSize();
	}
	else setSegSizeNot();

	SetupRenderer();
	pOnePaddle.x = 40;
	pOnePaddle.y = 350;
	pOnePaddle.w = 20;
	pOnePaddle.h = 118;

	pTwoPaddle.x = 1140;
	pTwoPaddle.y = 350;
	pTwoPaddle.w = 20;
	pTwoPaddle.h = 118;

	ball.w = 20;
	ball.h = 20;

	obstacle.h = 90;
	obstacle.w = 90;

	srand(time(NULL));
	resetGame();
	
	RunMultiPlayerGame();
}
int getRandomNumber(int high, int low)
{
	return rand() % (high - low + 1) + low;
}
void spawnPowerUp()
{
	if (toggle.powerUpsOn)
	{
		powerUp.h = 75;
		powerUp.w = 75;
		powerUp.x = getRandomNumber(810, 295);
		powerUp.y = getRandomNumber(720, 15);
	}
}

void SetupRenderer()
{
	SDL_RenderSetLogicalSize(gRenderer, 1200, 800);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
}
void Render()
{
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(gRenderer, &pOnePaddle);
	SDL_RenderFillRect(gRenderer, &pTwoPaddle);
	SDL_RenderFillRect(gRenderer, &ball);
	if (toggle.obstacleOn)
	{
		SDL_RenderFillRect(gRenderer, &obstacle);
	}
	if (toggle.powerUpsOn && powerHit == false && lastHit!=3)
	{
		if(head->value==1)
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
		else if(head->value==2)
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 0);
		else if(head->value==3)
			SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);
		SDL_RenderFillRect(gRenderer, &powerUp);
	}
	loadText(playerOneName);
	textTexture.render(250, 5);
	loadText(playerTwoName);
	textTexture.render(880, 5);
	loadText(scoreOne);
	textTexture.render(250, 50);
	loadText(scoreTwo);
	textTexture.render(880, 50);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderPresent(gRenderer);
}

void scoresTextUpdate()
{
	scoreBoard.open("Scores.txt", std::ios::app);
	scoreBoard << scoreOne << endl;
	scoreBoard << playerOneName << endl;
	scoreBoard << playerTwoName << endl;
	scoreBoard << scoreTwo << endl << endl;
	scoreBoard.close();

}
void endGameRender()
{
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	if (scoreOneCounter > scoreTwoCounter)
	{
		loadText(playerOneName);
		textTexture.render(450, 355);

	}
	else
	{
		loadText(playerTwoName);
		textTexture.render(450, 355);

	}

	textTexture.render(450, 355);
	loadText("Wins!");
	textTexture.render(450,400);
	loadText("press backspace to go back to the menu");
	textTexture.render(290, 555);


	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderPresent(gRenderer);
}
void resetBall()
{
	ball.x = ball_x;
	ball.y = ball_y;
	yDir = getRandomNumber(4, -4);
	xDir = getRandomNumber(4, -4);
	if ((yDir <= 2 && yDir >= -2) || (xDir <= 2 && xDir >= -2))
		resetBall();
}
void resetPaddle()
{
	pOnePaddle.h = 118;
	pOnePaddle.y = 350;
	pTwoPaddle.h = 118;
	pTwoPaddle.y = 350;
}
void resetObstacle()
{
	if (toggle.obstacleOn)
	{
		obstacle.x = obstacle_x;
		obstacle.y = obstacle_y;
	}
}
void nextPower()
{
	if (toggle.powerUpsOn)
		head = head->next;
}
void resetGame()
{
	resetBall();
	resetPaddle();
	resetObstacle();
	nextPower();
	spawnPowerUp();
	powerHit = false;
	buffApplied = false;
	speedOn = false;
	sizeApplied = 0;
	lastHit = 3;
}

bool segOne_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 >= (pOnePaddle.y - 5) && ball.y+ball.h/2 <= (pOnePaddle.y + 3 + paddleBuff.segOneIncrease))
		{
			yDir = -4;
			xDir = 1;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 >= (pOnePaddle.y - 5) && ball.y+ball.h/2 <= (pOnePaddle.y + 3))
		{
			yDir = -4;
			xDir = 1;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segTwo_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 3 + paddleBuff.segTwoIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 11 + paddleBuff.segTwoIncrease))
		{
			yDir = -4;
			xDir = 2;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 3) && ball.y+ball.h/2 <= (pOnePaddle.y + 11))
		{
			yDir = -4;
			xDir = 2;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segThree_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 11 + paddleBuff.segThreeIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 19 + paddleBuff.segThreeIncrease))
		{
			yDir = -4;
			xDir = 3;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 11) && ball.y+ball.h/2 <= (pOnePaddle.y + 19))
		{
			yDir = -4;
			xDir = 3;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segFour_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 19 + paddleBuff.segFourIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 27 + paddleBuff.segFourIncrease))
		{
			yDir = -4;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 19) && ball.y+ball.h/2 <= (pOnePaddle.y + 27))
		{
			yDir = -4;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segFive_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 27 + paddleBuff.segFiveIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 35 + paddleBuff.segFiveIncrease))
		{
			yDir = -3;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 27) && ball.y+ball.h/2 <= (pOnePaddle.y + 35))
		{
			yDir = -3;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segSix_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 35 + paddleBuff.segSixIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 43 + paddleBuff.segSixIncrease))
		{
			yDir = -2;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 35) && ball.y+ball.h/2 <= (pOnePaddle.y + 43))
		{
			yDir = -2;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segSeven_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 43 + paddleBuff.segSevenIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 51 + paddleBuff.segSevenIncrease))
		{
			yDir = -1;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 43) && ball.y+ball.h/2 <= (pOnePaddle.y + 51))
		{
			yDir = -1;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segEight_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 51 + paddleBuff.segEightIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 59 + paddleBuff.segEightIncrease))
		{
			yDir = 0;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 51) && ball.y+ball.h/2 <= (pOnePaddle.y + 59))
		{
			yDir = 0;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segNine_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 59 + paddleBuff.segNineIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 67 + paddleBuff.segNineIncrease))
		{
			yDir = 0;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 59) && ball.y+ball.h/2 <= (pOnePaddle.y + 67))
		{
			yDir = 0;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segTen_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 67 + paddleBuff.segTenIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 75 + paddleBuff.segTenIncrease))
		{
			yDir = 1;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 67) && ball.y+ball.h/2 <= (pOnePaddle.y + 75))
		{
			yDir = 1;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segEleven_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 75 + paddleBuff.segElevenIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 83 + paddleBuff.segElevenIncrease))
		{
			yDir = 2;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 75) && ball.y+ball.h/2 <= (pOnePaddle.y + 83))
		{
			yDir = 2;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segTwelve_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 83 + paddleBuff.segTwelveIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 91 + paddleBuff.segTwelveIncrease))
		{
			yDir = 3;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 83) && ball.y+ball.h/2 <= (pOnePaddle.y + 91))
		{
			yDir = 3;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segThirteen_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 91 + paddleBuff.segThirteenIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 99 + paddleBuff.segThirteenIncrease))
		{
			yDir = 4;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 91) && ball.y+ball.h/2 <= (pOnePaddle.y + 99))
		{
			yDir = 4;
			xDir = 4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segFourteen_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 99 + paddleBuff.segFourteenIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 107 + paddleBuff.segFourteenIncrease))
		{
			yDir = 4;
			xDir = 3;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 99) && ball.y+ball.h/2 <= (pOnePaddle.y + 107))
		{
			yDir = 4;
			xDir = 3;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segFifteen_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 107 + paddleBuff.segFifteenIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 115 + paddleBuff.segFifteenIncrease))
		{
			yDir = 4;
			xDir = 2;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 107) && ball.y+ball.h/2 <= (pOnePaddle.y + 115))
		{
			yDir = 4;
			xDir = 2;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segSixteen_pOne()
{
	if (sizeApplied == 1)
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 115 + paddleBuff.segSixteenIncrease) && ball.y+ball.h/2 <= (pOnePaddle.y + 123 + paddleBuff.segSixteenIncrease))
		{
			yDir = 4;
			xDir = 1;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pOnePaddle.y + 115) && ball.y+ball.h/2 <= (pOnePaddle.y + 123))
		{
			yDir = 4;
			xDir = 1;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}

bool ballIn_pOnePaddle()
{
	if (
		ball.x > pOnePaddle.x &&
		ball.x <= (pOnePaddle.x + pOnePaddle.w) &&
		(ball.y + ball.h/2) > (pOnePaddle.y - 5) &&
		ball.y+ball.h/2 < (pOnePaddle.y + pOnePaddle.h + 5)
		)
	{
		lastHit = 1;
		if (segOne_pOne())
			return true;
		else
			if (segTwo_pOne())
				return true;
			else
				if (segThree_pOne())
					return true;
				else
					if (segFour_pOne())
						return true;
					else
						if (segFive_pOne())
							return true;
						else
							if (segSix_pOne())
								return true;
							else
								if (segSeven_pOne())
									return true;
								else
									if (segEight_pOne())
										return true;
									else if (segNine_pOne())
										return true;
									else if (segTen_pOne())
										return true;
									else if (segEleven_pOne())
										return true;
									else if (segTwelve_pOne())
										return true;
									else if (segThirteen_pOne())
										return true;
									else if (segFourteen_pOne())
										return true;
									else if (segFifteen_pOne())
										return true;
									else if (segSixteen_pOne())
										return true;
	}	
	else return false;
}


bool segOne_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 >= (pTwoPaddle.y - 5) && ball.y+ball.h/2 <= (pTwoPaddle.y + 3 + paddleBuff.segOneIncrease))
		{
			yDir = -4;
			xDir = -1;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 >= (pTwoPaddle.y - 5) && ball.y+ball.h/2 <= (pTwoPaddle.y + 3))
		{
			yDir = -4;
			xDir = -1;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segTwo_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 3 + paddleBuff.segTwoIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 11 + paddleBuff.segTwoIncrease))
		{
			yDir = -4;
			xDir = -2;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 3) && ball.y+ball.h/2 <= (pTwoPaddle.y + 11))
		{
			yDir = -4;
			xDir = -2;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segThree_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 11 + paddleBuff.segThreeIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 19 + paddleBuff.segThreeIncrease))
		{
			yDir = -4;
			xDir = -3;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 11) && ball.y+ball.h/2 <= (pTwoPaddle.y + 19))
		{
			yDir = -4;
			xDir = -3;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segFour_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 19 + paddleBuff.segFourIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 27 + paddleBuff.segFourIncrease))
		{
			yDir = -4;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 19) && ball.y+ball.h/2 <= (pTwoPaddle.y + 27))
		{
			yDir = -4;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segFive_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 27 + paddleBuff.segFiveIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 35 + paddleBuff.segFiveIncrease))
		{
			yDir = -3;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 27) && ball.y+ball.h/2 <= (pTwoPaddle.y + 35))
		{
			yDir = -3;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segSix_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 35 + paddleBuff.segSixIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 43 + paddleBuff.segSixIncrease))
		{
			yDir = -2;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 35) && ball.y+ball.h/2 <= (pTwoPaddle.y + 43))
		{
			yDir = -2;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segSeven_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 43 + paddleBuff.segSevenIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 51 + paddleBuff.segSevenIncrease))
		{
			yDir = -1;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 43) && ball.y+ball.h/2 <= (pTwoPaddle.y + 51))
		{
			yDir = -1;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segEight_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 51 + paddleBuff.segEightIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 59 + paddleBuff.segEightIncrease))
		{
			yDir = 0;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 51) && ball.y+ball.h/2 <= (pTwoPaddle.y + 59))
		{
			yDir = 0;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segNine_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 59 + paddleBuff.segNineIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 67 + paddleBuff.segNineIncrease))
		{
			yDir = 0;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 59) && ball.y+ball.h/2 <= (pTwoPaddle.y + 67))
		{
			yDir = 0;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segTen_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 67 + paddleBuff.segTenIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 75 + paddleBuff.segTenIncrease))
		{
			yDir = 1;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 67) && ball.y+ball.h/2 <= (pTwoPaddle.y + 75))
		{
			yDir = 1;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segEleven_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 75 + paddleBuff.segElevenIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 83 + paddleBuff.segElevenIncrease))
		{
			yDir = 2;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 75) && ball.y+ball.h/2 <= (pTwoPaddle.y + 83))
		{
			yDir = 2;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segTwelve_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 83 + paddleBuff.segTwelveIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 91 + paddleBuff.segTwelveIncrease))
		{
			yDir = 3;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 83) && ball.y+ball.h/2 <= (pTwoPaddle.y + 91))
		{
			yDir = 3;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segThirteen_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 91 + paddleBuff.segThirteenIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 99 + paddleBuff.segThirteenIncrease))
		{
			yDir = 4;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 91) && ball.y+ball.h/2 <= (pTwoPaddle.y + 99))
		{
			yDir = 4;
			xDir = -4;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segFourteen_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 99 + paddleBuff.segFourteenIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 107 + paddleBuff.segFourteenIncrease))
		{
			yDir = 4;
			xDir = -3;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 99) && ball.y+ball.h/2 <= (pTwoPaddle.y + 107))
		{
			yDir = 4;
			xDir = -3;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segFifteen_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 107 + paddleBuff.segFifteenIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 115 + paddleBuff.segFifteenIncrease))
		{
			yDir = 4;
			xDir = -2;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 107) && ball.y+ball.h/2 <= (pTwoPaddle.y + 115))
		{
			yDir = 4;
			xDir = -2;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}
bool segSixteen_pTwo()
{
	if (sizeApplied == 2)
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 115 + paddleBuff.segSixteenIncrease) && ball.y+ball.h/2 <= (pTwoPaddle.y + 123 + paddleBuff.segSixteenIncrease))
		{
			yDir = 4;
			xDir = -1;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
	else
	{
		if (ball.y+ball.h/2 > (pTwoPaddle.y + 115) && ball.y+ball.h/2 <= (pTwoPaddle.y + 123))
		{
			yDir = 4;
			xDir = -1;
			if (speedOn)
			{
				yDir = 2 * yDir;
				xDir = 2 * xDir;
			}
			return true;
		}
		else return false;
	}
}

bool ballIn_pTwoPaddle()
{
	if (
		ball.x < pTwoPaddle.x &&
		(ball.x + ball.w) >= pTwoPaddle.x &&
		(ball.y+ball.h/2) > (pTwoPaddle.y-5) &&
		(ball.y+ball.h/2) < (pTwoPaddle.y + pTwoPaddle.h+5)
		)
	{
		lastHit = 2;
		if (segOne_pTwo())
			return true;
		else
			if (segTwo_pTwo())
				return true;
			else
				if (segThree_pTwo())
					return true;
				else
					if (segFour_pTwo())
						return true;
					else
						if (segFive_pTwo())
							return true;
						else
							if (segSix_pTwo())
								return true;
							else
								if (segSeven_pTwo())
									return true;
								else
									if (segEight_pTwo())
										return true;
									else if (segNine_pTwo())
										return true;
									else if (segTen_pTwo())
										return true;
									else if (segEleven_pTwo())
										return true;
									else if (segTwelve_pTwo())
										return true;
									else if (segThirteen_pTwo())
										return true;
									else if (segFourteen_pTwo())
										return true;
									else if (segFifteen_pTwo())
										return true;
									else if (segSixteen_pTwo())
										return true;
	}
	else return false;
}

bool ballIn_obstacle()
{
	if (
		ball.x >= obstacle.x &&
		ball.x <= (obstacle.x + obstacle.w) &&
		(ball.y + ball.h/2) >= obstacle.y &&
		ball.y+ball.h/2 <= (obstacle.y + obstacle.h)
		)	
		return true;	
	else
		if (
			(ball.x + ball.w) >= obstacle.x &&
			(ball.x + ball.w) <= (obstacle.x + obstacle.w) &&
			(ball.y + ball.h/2) >= obstacle.y &&
			ball.y+ball.h/2 <= (obstacle.y + obstacle.h)
			)		
			return true;		
		else return false;;

}
bool ballIn_powerUp()
{
	if (
		ball.x >= powerUp.x &&
		ball.x <= (powerUp.x + powerUp.w) &&
		(ball.y + ball.h)/2 >= powerUp.y &&
		ball.y+ball.h/2 <= (powerUp.y + powerUp.h)
		)
	{
		powerHit = true;
		return true;
	}
	else
		if (
			(ball.x+ball.w) >= powerUp.x &&
			(ball.x+ball.w) <= (powerUp.x + powerUp.w) &&
			(ball.y + ball.h/2) >= powerUp.y &&
			ball.y+ball.h/2 <= (powerUp.y + powerUp.h)
			)
		{
			powerHit = true;
			return true;
		}
		else return false;
}

void paddleOneBig()
{
	pOnePaddle.h += paddleBuff.sizeIncrease;
	pOnePaddle.y -= (paddleBuff.sizeIncrease / 2);
	sizeApplied = 1;
}
void paddleTwoBig()
{
	pTwoPaddle.h += paddleBuff.sizeIncrease;
	pTwoPaddle.y -= (paddleBuff.sizeIncrease / 2);
	sizeApplied = 2;
}
void paddleSize()
{
	if (lastHit == 1)
		paddleOneBig();
	else
		if(lastHit==2)
			paddleTwoBig();
}
void speedPlus()
{
	xDir = 2 * xDir;
	yDir = 2 * yDir;
	speedOn = true;
}
void instaWin()
{
	if (lastHit == 1)
	{
		scoreOneCounter++;
		scoreOne = intToString(scoreOneCounter);
		resetGame();
		gameStart = false;
		if (scoreOneCounter == maxPoints || scoreTwoCounter == maxPoints)
			gameOver = true;
	}
	else
		if (lastHit == 2)
		{
			scoreTwoCounter++;
			scoreTwo = intToString(scoreTwoCounter);
			resetGame();
			gameStart = false;
			if (scoreOneCounter == maxPoints || scoreTwoCounter == maxPoints)
				gameOver = true;
		}
}
void applyBuff()
{
	int buffNumber = head->value;
	if (buffNumber == 1)
		paddleSize();
	else if (buffNumber == 2)
		speedPlus();
	buffApplied = true;
	if (buffNumber == 3)
		instaWin();
}

bool ballExit()
{
	if (ball.x < 1)
	{
		scoreTwoCounter++;
		scoreTwo = intToString(scoreTwoCounter);
		return true;
	}
	if (ball.x > 1180)
	{
		scoreOneCounter++;
		scoreOne = intToString(scoreOneCounter);
		return true;
	}
	 return false;
}
void paddleExit()
{
	if (pOnePaddle.y < 1)
		pOnePaddle.y = 1;
	else
		if (pOnePaddle.y + pOnePaddle.h > 799)
			pOnePaddle.y = 799 - pOnePaddle.h;
	if (pTwoPaddle.y < 1)
		pTwoPaddle.y = 1;
	else
		if (pTwoPaddle.y + pTwoPaddle.h > 799)
			pTwoPaddle.y = 799 - pTwoPaddle.h;
}
void ballCollision()
{
	if (ball.y < 1)
	{
		yDir -= 2 * yDir;
		ball.y = 1;
	}
	else
		if (ball.y + ball.h > 799)
		{
			yDir -= 2 * yDir;
			ball.y = 799-ball.h;
		}

	if (ballIn_pOnePaddle())
	{		
		ball.x = pOnePaddle.x + pOnePaddle.w;
	}
	else
		if (ballIn_pTwoPaddle())
		{		
			ball.x = pTwoPaddle.x - ball.w;
		}
		else
		{
			if (toggle.obstacleOn)
			{
				if (ballIn_obstacle())
				{
					yDir -= 2 * yDir;
					xDir -= 2 * xDir;
				}
			}			
			if (toggle.powerUpsOn)
			{
				if (ballIn_powerUp() && lastHit != 3 && buffApplied == false)
					applyBuff();
			}
		}
}
void moveObstacle()
{
	obstacle.y += obstacleDir;
	if (obstacle.y < 21)
	{
		obstacleDir -= 2 * obstacleDir;
		obstacle.y = 21;
	}
	else
		if (obstacle.y + obstacle.h > 779)
		{
			obstacleDir -= 2 * obstacleDir;
			obstacle.y = 779 - obstacle.h;
		}
}
void moveBall()
{
	ball.x += xDir;
	ball.y += yDir;
	if (toggle.obstacleOn)
		moveObstacle();
	ballCollision();
	if (ballExit())
	{
		if (scoreOneCounter == maxPoints || scoreTwoCounter == maxPoints)
			gameOver = true;
		resetGame();
		gameStart = false;
	}
}
void RunMultiPlayerGame()
{

	SDL_Event event;
	while (GAME)
	{

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				GAME = false;
				break;
			}
		}
			
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (gameStart == false)
			{
				if (currentKeyStates[SDL_SCANCODE_SPACE])
						gameStart = true;
			}	
			if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_UP])
			{
				pOnePaddle.y -= 5;
				pTwoPaddle.y -= 5;	
			}
			else
				if (currentKeyStates[SDL_SCANCODE_S] && currentKeyStates[SDL_SCANCODE_DOWN])
				{
					pOnePaddle.y += 5;
					pTwoPaddle.y += 5;	
				}
				else
					if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_DOWN])
					{
						pOnePaddle.y -= 5;
						pTwoPaddle.y += 5;
					}
					else
						if (currentKeyStates[SDL_SCANCODE_S] && currentKeyStates[SDL_SCANCODE_UP])
						{
							pOnePaddle.y += 5;
							pTwoPaddle.y -= 5;		
						}
						else
						{
							if (currentKeyStates[SDL_SCANCODE_UP])
							{
								pTwoPaddle.y -= 5;	
							}
							else if (currentKeyStates[SDL_SCANCODE_DOWN])
							{
								pTwoPaddle.y += 5;	
							}
							if (currentKeyStates[SDL_SCANCODE_W])
							{
								pOnePaddle.y -= 5;	
							}
							else if (currentKeyStates[SDL_SCANCODE_S])
							{
								pOnePaddle.y += 5;
							}
						}		
		paddleExit();
		if (gameStart == true)
			moveBall();
		paddleExit();
	        if (gameOver)
		{
			GAME = false;
			scoresTextUpdate();
		}
		Render();
		SDL_Delay(8);
	}

	while (gameOver)
	{
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
			{
				gameOver = false;
				break;
			}
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_BACKSPACE])
		{
			currentMenu = MENU;
			currentButton = START_BUTTON;
			updateScreen(START_BUTTON);
			GAME = true;
			scoreOne = "0";
			scoreTwo = "0";
			scoreOneCounter = 0;
			scoreTwoCounter = 0;
			gameOver = false;
			gameStart = false;
			break;
		}
		endGameRender();
		SDL_Delay(8);
	}
}
