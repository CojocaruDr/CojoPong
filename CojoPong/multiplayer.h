#include<ctime>

const int ball_x = 590;
const int ball_y = 390;
int xDir, yDir;
bool gameStart = false;

void SetupRenderer();
void Render();
void RunGame();

void resetBall();

SDL_Rect pOnePaddle;
SDL_Rect pTwoPaddle;
SDL_Rect ball;

void multiPlayer()
{
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
	if (ball.y > (pOnePaddle.y + 25) && ball.y <= (pOnePaddle.y + 30))
	{
		yDir = -3;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segFour_pOne()
{
	if (ball.y > (pOnePaddle.y + 30) && ball.y <= (pOnePaddle.y + 45))
	{
		yDir = -1;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segFive_pOne()
{
	if (ball.y > (pOnePaddle.y + 45) && ball.y <= (pOnePaddle.y + 60))
	{
		yDir = 1;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segSix_pOne()
{
	if (ball.y > (pOnePaddle.y + 60) && ball.y <= (pOnePaddle.y + 75))
	{
		yDir = 3;
		xDir = 4;
		return true;
	}
	else return false;
}
bool segSeven_pOne()
{
	if (ball.y > (pOnePaddle.y + 75) && ball.y <= (pOnePaddle.y + 90))
	{
		yDir = 4;
		xDir = 3;
		return true;
	}
	else return false;
}
bool segEight_pOne()
{
	if (ball.y > (pOnePaddle.y + 30) && ball.y <= (pOnePaddle.y + 45))
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
		(ball.y + ball.h) > (pOnePaddle.y + 5) &&
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
	if (ball.y > (pTwoPaddle.y + 25) && ball.y <= (pTwoPaddle.y + 30))
	{
		yDir = -3;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segFour_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 30) && ball.y <= (pTwoPaddle.y + 45))
	{
		yDir = -1;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segFive_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 45) && ball.y <= (pTwoPaddle.y + 60))
	{
		yDir = 1;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segSix_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 60) && ball.y <= (pTwoPaddle.y + 75))
	{
		yDir = 3;
		xDir = -4;
		return true;
	}
	else return false;
}
bool segSeven_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 75) && ball.y <= (pTwoPaddle.y + 90))
	{
		yDir = 4;
		xDir = -3;
		return true;
	}
	else return false;
}
bool segEight_pTwo()
{
	if (ball.y > (pTwoPaddle.y + 30) && ball.y <= (pTwoPaddle.y + 45))
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
		(ball.y+ball.h) > (pTwoPaddle.y+5) &&
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


bool ballExit()
{
	if (ball.x < 1 || ball.x > 1180)
		return true;
	else return false;
}
void ballCollision()
{
	if (ball.y < 1)
		yDir -= 2 * yDir;
	else
		if (ball.y + ball.h > 799)
			yDir -= 2 * yDir;


	if (ballIn_pOnePaddle())
	{		
		ball.x = pOnePaddle.x + pOnePaddle.w;
	}
	else
		if (ballIn_pTwoPaddle())
		{		
			ball.x = pTwoPaddle.x - ball.w;
		}
}
void moveBall()
{
	ball.x += xDir;
	ball.y += yDir;
	ballCollision();
	if (ballExit())
	{
		resetBall();
		gameStart = false;
	}

}
void RunGame()
{
	bool loop = true;
	SDL_Event event;
	while (loop)
	{

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				loop = false;
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
		Render();
		SDL_Delay(8);
	}
}
