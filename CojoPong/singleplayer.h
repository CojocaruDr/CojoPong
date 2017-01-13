#include "multiplayer.h"
#include "MenuFunctions.h"
void moveAiPaddleEasy()
{
	if ((pTwoPaddle.y + pTwoPaddle.h / 2) <= (ball.y + ball.h / 2))
		pTwoPaddle.y += 2;
	else
		if ((pTwoPaddle.y + pTwoPaddle.h / 2) > (ball.y + ball.h / 2))
			pTwoPaddle.y -= 2;
}
void moveAiPaddleNormal()
{
	if ((pTwoPaddle.y + pTwoPaddle.h / 2) <= (ball.y + ball.h / 2))
		pTwoPaddle.y += 5;
	else
		if ((pTwoPaddle.y + pTwoPaddle.h / 2) > (ball.y + ball.h / 2))
			pTwoPaddle.y -= 5;
}
void moveAiPaddleHard()
{
	if ((pTwoPaddle.y + pTwoPaddle.h / 2) <= (ball.y + ball.h / 2))
		pTwoPaddle.y += 7;
	else
		if ((pTwoPaddle.y + pTwoPaddle.h / 2) > (ball.y + ball.h / 2))
			pTwoPaddle.y -= 7;
}

void RunSinglePlayerGame()
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
		else
			if (currentKeyStates[SDL_SCANCODE_W])
			{
				pOnePaddle.y -= 5;
			}
			else if (currentKeyStates[SDL_SCANCODE_S])
			{
				pOnePaddle.y += 5;
			}
		if (toggle.AI_Difficulty==0)
			moveAiPaddleEasy();
		else
			if (toggle.AI_Difficulty==1)
				moveAiPaddleNormal();
			else
				moveAiPaddleHard();
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
void singlePlayer()
{
	lastHit = 3;

	if (toggle.points == true)
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

	RunSinglePlayerGame();
}
