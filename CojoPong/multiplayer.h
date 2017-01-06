#include <ctime>
#include "MenuFunctions.h"
#include <sstream>



const int ball_x = 580;
const int ball_y = 390;
const int obstacle_x = 545;
const int obstacle_y = 21;
int xDir, yDir,obstacleDir=5,scoreOneCounter=0,scoreTwoCounter=0,maxPoints;
std::string scoreOne,scoreTwo;
bool gameStart = false;
bool GAME = true;
bool gameOver = false;

void SetupRenderer();
void Render();
void RunGame();

void resetBall();

SDL_Rect pOnePaddle;
SDL_Rect pTwoPaddle;
SDL_Rect ball;
SDL_Rect obstacle;


void multiPlayer()
{
	TTF_Init();
	toggle.points = true;
	if (toggle.points == true)
		maxPoints = 5;
	else
		maxPoints = 10;
	SetupRenderer();
	pOnePaddle.x = 40;
	pOnePaddle.y = 350;
	pOnePaddle.w = 20;
	pOnePaddle.h = 110;

	pTwoPaddle.x = 1140;
	pTwoPaddle.y = 350;
	pTwoPaddle.w = 20;
	pTwoPaddle.h = 110;

	ball.w = 20;
	ball.h = 20;

	obstacle.h = 90;
	obstacle.w = 90;

	srand(time(NULL));
	resetBall();
	RunGame();
}
int getRandomNumber(int high, int low)
{
	return rand() % (high - low + 1) + low;
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
	loadText(scoreOne);
	textTexture.render(300, 5);
	loadText(scoreTwo);
	textTexture.render(880, 5);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderPresent(gRenderer);
}
void endGameRender()
{
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	if (scoreOneCounter > scoreTwoCounter)
	{
		loadText("player one wins");
		textTexture.render(450, 355);
		loadText("press backspace to go back to the menu");
		textTexture.render(290, 555);
	}
	else
	{
		loadText("player two wins");
		textTexture.render(450, 355);
		loadText("press backspace to go back to the menu");
		textTexture.render(290, 555);
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderPresent(gRenderer);
}
void resetBall()
{
	if (toggle.obstacleOn)
	{
		obstacle.x = obstacle_x;
		obstacle.y = obstacle_y;
	}
	ball.x = ball_x;
	ball.y = ball_y;
	yDir = getRandomNumber(4, -4);
	xDir = getRandomNumber(4, -4);
	if ((yDir <= 2 && yDir >= -2) || (xDir <= 2 && xDir >= -2))
		resetBall();
}
void SetupRenderer()
{
	SDL_RenderSetLogicalSize(gRenderer, 1200, 800);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
}


bool segOne_pOne()
{
	if (ball.y >= (pOnePaddle.y - 5) && ball.y <= (pOnePaddle.y + 10))
	{
		yDir = -4;
		xDir = 2;
		return true;
	}
	else return false;
}
bool segTwo_pOne()
{
	if (ball.y > (pOnePaddle.y + 10) && ball.y <= (pOnePaddle.y + 25))
	{
		yDir = -4;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segThree_pOne()
{
	if (ball.y > (pOnePaddle.y + 25) && ball.y <= (pOnePaddle.y + 40))
	{
		yDir = -3;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segFour_pOne()
{
	if (ball.y > (pOnePaddle.y + 40) && ball.y <= (pOnePaddle.y + 55))
	{
		yDir = -1;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segFive_pOne()
{
	if (ball.y > (pOnePaddle.y + 55) && ball.y <= (pOnePaddle.y + 70))
	{
		yDir = 1;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segSix_pOne()
{
	if (ball.y > (pOnePaddle.y + 70) && ball.y <= (pOnePaddle.y + 85))
	{
		yDir = 3;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segSeven_pOne()
{
	if (ball.y > (pOnePaddle.y + 85) && ball.y <= (pOnePaddle.y + 100))
	{
		yDir = 4;
		xDir = 3;
		return true;
	}
	else return false;
}
bool segEight_pOne()
{
	if (ball.y > (pOnePaddle.y + 100) && ball.y <= (pOnePaddle.y + 115))
	{
		yDir = 4;
		xDir = 2;
		return true;
	}
	else return false;
}

bool ballIn_pOnePaddle()
{
	if (
		ball.x > pOnePaddle.x &&
		ball.x <= (pOnePaddle.x + pOnePaddle.w) &&
		(ball.y + ball.h) > (pOnePaddle.y - 5) &&
		ball.y < (pOnePaddle.y + pOnePaddle.h + 5)
		)
	{
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
	}
		
	else return false;
}


bool segOne_pTwo()
{
	if (ball.y >= (pTwoPaddle.y - 5) && ball.y <= (pTwoPaddle.y + 10))
	{
		yDir = -4;
		xDir = -2;
		return true;
	}
	else return false;
}
bool segTwo_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 10) && ball.y <= (pTwoPaddle.y + 25))
	{
		yDir = -4;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segThree_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 25) && ball.y <= (pTwoPaddle.y + 40))
	{
		yDir = -3;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segFour_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 40) && ball.y <= (pTwoPaddle.y + 55))
	{
		yDir = -1;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segFive_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 55) && ball.y <= (pTwoPaddle.y + 70))
	{
		yDir = 1;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segSix_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 70) && ball.y <= (pTwoPaddle.y + 85))
	{
		yDir = 3;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segSeven_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 85) && ball.y <= (pTwoPaddle.y + 100))
	{
		yDir = 4;
		xDir = -3;
		return true;
	}
	else return false;
}
bool segEight_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 100) && ball.y <= (pTwoPaddle.y + 115))
	{
		yDir = 4;
		xDir = -2;
		return true;
	}
	else return false;
}

bool ballIn_pTwoPaddle()
{
	if (
		ball.x < pTwoPaddle.x &&
		(ball.x + ball.w) >= pTwoPaddle.x &&
		(ball.y+ball.h) > (pTwoPaddle.y-5) &&
		ball.y < (pTwoPaddle.y + pTwoPaddle.h+5)
		)
	{
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
	}
	else return false;
}

bool ballIn_obstacle()
{
	if (
		ball.x >= obstacle.x &&
		ball.x <= (obstacle.x + obstacle.w) &&
		(ball.y + ball.h) >= obstacle.y &&
		ball.y <= (obstacle.y + obstacle.h)
		)
		return true;
	else return false;

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
			if (toggle.obstacleOn)
				if (ballIn_obstacle())
				{
					yDir -= 2 * yDir;
					xDir -= 2 * xDir;
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
		resetBall();
		gameStart = false;
	}

}
void RunGame()
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
		if (gameStart == true)
			moveBall();
		if (gameOver)
			GAME = false;
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
/*		if (currentKeyStates[SDL_SCANCODE_BACKSPACE])
		{
			currentMenu = MENU;
			currentButton = START_BUTTON;
			updateScreen(START_BUTTON);
		}*/
		endGameRender();
		SDL_Delay(8);
	}
}
