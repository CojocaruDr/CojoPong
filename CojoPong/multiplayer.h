#include <ctime>
#include "MenuFunctions.h"
#include <sstream>

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
int lastHit;

void resetGame();
void SetupRenderer();
void Render();
void RunGame();
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
}paddleBuff;

struct node {
	int value;
	node* next;
};
node *head;
node *tail;

void createPowerUpsQueue()
{
	head = new node;
	head->value = getRandomNumber(3, 1);
	head->next = NULL;
	tail = head;
	int position;
	for (position = 0; position < 19; position++)
	{
		tail = tail->next;
		tail = new node;
		tail->value = getRandomNumber(3, 1);
		tail->next = NULL;
	}
}
void setSegSize()
{
	paddleBuff.sizeIncrease = 40;
	paddleBuff.segOneIncrease = 5;
	paddleBuff.segTwoIncrease = 10;
	paddleBuff.segOneIncrease = 15;
	paddleBuff.segOneIncrease = 20;
	paddleBuff.segOneIncrease = 25;
	paddleBuff.segOneIncrease = 30;
	paddleBuff.segOneIncrease = 35;
	paddleBuff.segOneIncrease = 40;
}
void setSegSizeNot()
{
	paddleBuff.segOneIncrease = 0;
	paddleBuff.segTwoIncrease = 0;
	paddleBuff.segOneIncrease = 0;
	paddleBuff.segOneIncrease = 0;
	paddleBuff.segOneIncrease = 0;
	paddleBuff.segOneIncrease = 0;
	paddleBuff.segOneIncrease = 0;
	paddleBuff.segOneIncrease = 0;
}
void multiPlayer()
{
	TTF_Init();
	lastHit = 3;
	toggle.points = true;
	toggle.powerUpsOn = true;

	if (toggle.points == true)
		maxPoints = 5;
	else
		maxPoints = 10;
	if (toggle.powerUpsOn)
	{
		createPowerUpsQueue();
		setSegSize();
	}
	else setSegSizeNot();

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
	resetGame();
	RunGame();
}
int getRandomNumber(int high, int low)
{
	return rand() % (high - low + 1) + low;
}
void spawnPowerUp()
{
	if (toggle.powerUpsOn)
	{
		powerUp.h = 50;
		powerUp.w = 50;
		powerUp.x = getRandomNumber(835, 295);
		powerUp.y = getRandomNumber(745, 5);
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
		SDL_RenderFillRect(gRenderer, &powerUp);
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
	ball.x = ball_x;
	ball.y = ball_y;
	yDir = getRandomNumber(4, -4);
	xDir = getRandomNumber(4, -4);
	if ((yDir <= 2 && yDir >= -2) || (xDir <= 2 && xDir >= -2))
		resetBall();
}
void resetPaddle()
{
	pOnePaddle.h = 110;
	pOnePaddle.y = 350;
	pTwoPaddle.h = 110;
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
	if(toggle.powerUpsOn)
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
	lastHit = 3;
}

bool segOne_pOne()
{
	if (ball.y >= (pOnePaddle.y - 5) && ball.y <= (pOnePaddle.y + 10 + paddleBuff.segOneIncrease))
	{
		yDir = -4;
		xDir = 2;
		return true;
	}
	else return false;
}
bool segTwo_pOne()
{
	if (ball.y > (pOnePaddle.y + 10 + paddleBuff.segTwoIncrease) && ball.y <= (pOnePaddle.y + 25 + paddleBuff.segTwoIncrease))
	{
		yDir = -4;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segThree_pOne()
{
	if (ball.y > (pOnePaddle.y + 25 + paddleBuff.segThreeIncrease) && ball.y <= (pOnePaddle.y + 40 + paddleBuff.segThreeIncrease))
	{
		yDir = -3;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segFour_pOne()
{
	if (ball.y > (pOnePaddle.y + 40 + paddleBuff.segFourIncrease) && ball.y <= (pOnePaddle.y + 55 + paddleBuff.segFourIncrease))
	{
		yDir = -1;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segFive_pOne()
{
	if (ball.y > (pOnePaddle.y + 55 + paddleBuff.segFiveIncrease) && ball.y <= (pOnePaddle.y + 70 + paddleBuff.segFiveIncrease))
	{
		yDir = 1;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segSix_pOne()
{
	if (ball.y > (pOnePaddle.y + 70 + paddleBuff.segSixIncrease) && ball.y <= (pOnePaddle.y + 85 + paddleBuff.segSixIncrease))
	{
		yDir = 3;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segSeven_pOne()
{
	if (ball.y > (pOnePaddle.y + 85 + paddleBuff.segSevenIncrease) && ball.y <= (pOnePaddle.y + 100 + paddleBuff.segSevenIncrease))
	{
		yDir = 4;
		xDir = 3;
		return true;
	}
	else return false;
}
bool segEight_pOne()
{
	if (ball.y > (pOnePaddle.y + 100 + paddleBuff.segEightIncrease) && ball.y <= (pOnePaddle.y + 115 + paddleBuff.segEightIncrease))
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
	}
		
	else return false;
}


bool segOne_pTwo()
{
	if (ball.y >= (pTwoPaddle.y - 5) && ball.y <= (pTwoPaddle.y + 10 + paddleBuff.segOneIncrease))
	{
		yDir = -4;
		xDir = -2;
		return true;
	}
	else return false;
}
bool segTwo_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 10 + paddleBuff.segTwoIncrease) && ball.y <= (pTwoPaddle.y + 25 + paddleBuff.segTwoIncrease))
	{
		yDir = -4;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segThree_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 25 + paddleBuff.segThreeIncrease) && ball.y <= (pTwoPaddle.y + 40 + paddleBuff.segThreeIncrease))
	{
		yDir = -3;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segFour_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 40 + paddleBuff.segFourIncrease) && ball.y <= (pTwoPaddle.y + 55 + paddleBuff.segFourIncrease))
	{
		yDir = -1;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segFive_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 55 + paddleBuff.segFiveIncrease) && ball.y <= (pTwoPaddle.y + 70 + paddleBuff.segFiveIncrease))
	{
		yDir = 1;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segSix_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 70 + paddleBuff.segSixIncrease) && ball.y <= (pTwoPaddle.y + 85 + paddleBuff.segSixIncrease))
	{
		yDir = 3;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segSeven_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 85 + paddleBuff.segSevenIncrease) && ball.y <= (pTwoPaddle.y + 100 + paddleBuff.segSevenIncrease))
	{
		yDir = 4;
		xDir = -3;
		return true;
	}
	else return false;
}
bool segEight_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 100 + paddleBuff.segEightIncrease) && ball.y <= (pTwoPaddle.y + 115 + paddleBuff.segEightIncrease))
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
bool ballIn_powerUp()
{
	if (
		ball.x >= powerUp.x &&
		ball.x <= (powerUp.x + powerUp.w) &&
		(ball.y + ball.h) >= powerUp.y &&
		ball.y <= (powerUp.y + powerUp.h)
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
}
void paddleTwoBig()
{
	pTwoPaddle.h += paddleBuff.sizeIncrease;
	pTwoPaddle.y -= (paddleBuff.sizeIncrease / 2);
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
}

void instaWin()
{
	if (lastHit == 1)
	{
		scoreOneCounter++;
		scoreOne = intToString(scoreOneCounter);
		resetGame();
		gameStart = false;
	}
	else
	{
		scoreTwoCounter++;
		scoreTwo = intToString(scoreTwoCounter);
		resetGame();
		gameStart = false;
	}
}

void applyBuff()
{
	if (head->value == 1)
		paddleSize();
	else if (head->value == 2)
		speedPlus();
	else if (head->value == 3)
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
			if (toggle.obstacleOn)
			{
				if (ballIn_obstacle())
				{
					yDir -= 2 * yDir;
					xDir -= 2 * xDir;
				}
			}
			else
				if (toggle.powerUpsOn)
				{
					if (ballIn_powerUp())
						applyBuff();
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
		paddleExit();
		if (gameStart == true)
			moveBall();
		paddleExit();
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
