#pragma once
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

int posX = 100;
int posY = 200;
int sizeX = 300;
int sizeY = 400;

//SDL_Renderer* MRenderer;
// ADAUGA RENDER NOU PT MULTIPLAYER!! (rename gRenderer -> MRenderer)

void SetupRenderer();
void Render();
void RunGame();

SDL_Rect playerPaddle;
SDL_Rect AIPaddle;

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

	RunGame();
}
void Render()
{
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(gRenderer, &playerPaddle);
	SDL_RenderFillRect(gRenderer, &AIPaddle);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderPresent(gRenderer);
}

void SetupRenderer()
{
	SDL_RenderSetLogicalSize(gRenderer, 1200, 800);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
}
void RunGame()
{
	bool loop = true;

	while (loop)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				loop = false;
				break;
			}
			else
			{
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_UP])
				{
					playerPaddle.y -= 10;
					AIPaddle.y -= 10;
					break;
				}
				else
					if (currentKeyStates[SDL_SCANCODE_S] && currentKeyStates[SDL_SCANCODE_DOWN])
					{
						playerPaddle.y += 10;
						AIPaddle.y += 10;
						break;
					}
					else
						if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_DOWN])
						{
							playerPaddle.y -= 10;
							AIPaddle.y += 10;
							break;
						}
						else
							if (currentKeyStates[SDL_SCANCODE_S] && currentKeyStates[SDL_SCANCODE_UP])
							{
								playerPaddle.y += 10;
								AIPaddle.y -= 10;
								break;
							}
							else
							{
								if (currentKeyStates[SDL_SCANCODE_UP])
								{
									AIPaddle.y -= 10;
									break;
								}
								else if (currentKeyStates[SDL_SCANCODE_DOWN])
								{
									AIPaddle.y += 10;
									break;
								}
								if (currentKeyStates[SDL_SCANCODE_W])
								{
									playerPaddle.y -= 10;
									break;
								}
								else if (currentKeyStates[SDL_SCANCODE_S])
								{
									playerPaddle.y += 10;
									break;
								}
							}
			}
		}
		Render();
		SDL_Delay(16);
	}
}