#include<ctime>

const int ball_x = 590;
const int ball_y = 390;
int xDir, yDir;
bool gameStart = false;

void SetupRenderer();
void Render();
void RunGame();

void resetBall();

SDL_Rect playerPaddle;
SDL_Rect AIPaddle;
SDL_Rect ball;

void multiPlayer()
{
	SetupRenderer();

	playerPaddle.x = 20;
	playerPaddle.y = 350;
	playerPaddle.w = 20;
	playerPaddle.h = 100;

	AIPaddle.x = 1160;
	AIPaddle.y = 350;
	AIPaddle.w = 20;
	AIPaddle.h = 100;

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
	SDL_RenderFillRect(gRenderer, &playerPaddle);
	SDL_RenderFillRect(gRenderer, &AIPaddle);
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
bool ballInPOnePaddle()
{
	if (
		ball.y > playerPaddle.y &&
		ball.x <= (playerPaddle.x + playerPaddle.w) &&
		ball.y < (playerPaddle.y + playerPaddle.h))
		return true;
	else return false;
}
bool ballInPTwoPaddle()
{
	if ((ball.x + ball.w) >= AIPaddle.x &&
		(ball.y + ball.h) > AIPaddle.y &&
		ball.y < (AIPaddle.y + AIPaddle.h))
		return true;
	else return false;
}
bool ballExit()
{
	if (ball.x < 36 || ball.x > 1146)
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


	if (ballInPOnePaddle())
		xDir -= 2 * xDir;
	else
		if (ballInPTwoPaddle())
			xDir -= 2 * xDir;
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
				else
				{
					if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_UP])
					{
						playerPaddle.y -= 5;
						AIPaddle.y -= 5;	
					}
					else
						if (currentKeyStates[SDL_SCANCODE_S] && currentKeyStates[SDL_SCANCODE_DOWN])
						{
							playerPaddle.y += 5;
							AIPaddle.y += 5;	
						}
						else
							if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_DOWN])
							{
								playerPaddle.y -= 5;
								AIPaddle.y += 5;
							}
							else
								if (currentKeyStates[SDL_SCANCODE_S] && currentKeyStates[SDL_SCANCODE_UP])
								{
									playerPaddle.y += 5;
									AIPaddle.y -= 5;		
								}
								else
								{
									if (currentKeyStates[SDL_SCANCODE_UP])
									{
										AIPaddle.y -= 5;	
									}
									else if (currentKeyStates[SDL_SCANCODE_DOWN])
									{
										AIPaddle.y += 5;	
									}
									if (currentKeyStates[SDL_SCANCODE_W])
									{
										playerPaddle.y -= 5;	
									}
									else if (currentKeyStates[SDL_SCANCODE_S])
									{
										playerPaddle.y += 5;
									}
								}
				}
			
		
		if (playerPaddle.y < 1)
			playerPaddle.y = 1;
		else
			if (playerPaddle.y + playerPaddle.h > 799)
				playerPaddle.y = 799 - playerPaddle.h;
		if (AIPaddle.y < 1)
			AIPaddle.y = 1;
		else
			if (AIPaddle.y + AIPaddle.h > 799)
				AIPaddle.y = 799 - AIPaddle.h;
		if (gameStart == true)
			moveBall();
		Render();
		SDL_Delay(8);
	}
}
