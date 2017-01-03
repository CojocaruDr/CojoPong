#pragma once
#include <iostream>
using namespace std;


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;


bool SDL_StartUp();
bool loadMedia(std::string);
void close();
SDL_Texture* loadTexture(std::string path);
void createButton(short, short, short, short, std::string);

enum {
	START_BUTTON,
	OPTIONS_BUTTON,
	SCORES_BUTTON,
	QUIT_BUTTON
};

SDL_Window* pongWindow = NULL;
SDL_Surface* BG_Surface = NULL;
SDL_Surface* BG_Image = NULL;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* loadTexture(std::string path);

bool SDL_StartUp()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		pongWindow = SDL_CreateWindow("CojoPong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (pongWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(pongWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return true;
}

SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

bool loadMedia(std::string path)
{
	gTexture = loadTexture(path);
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		return false;
	}
	return true;
}

void close()
{

	SDL_FreeSurface(BG_Image);
	BG_Image = NULL;

	SDL_DestroyWindow(pongWindow);
	pongWindow = NULL;

	SDL_Quit();
}

void createButton(short x, short y, short width, short height, std::string path)
{
	SDL_Rect button;
	button.x = x;
	button.y = y;
	button.w = width;
	button.h = height;

	if (!loadMedia(path))
	{
		printf("Failed to load button %s ! SDL Error: %s", path, SDL_GetError());
		return;
	}
	else
	{
		SDL_RenderSetViewport(gRenderer, &button);
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	}

}

void updateScreen(char selectedButton)
{

	SDL_RenderClear(gRenderer);
	SDL_RenderSetViewport(gRenderer, NULL);
	loadMedia("Resources/Menu_BG.bmp");
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

	SDL_RenderPresent(gRenderer);


	if (selectedButton == START_BUTTON)
	{
		createButton(450, 240, 300, 80, "Resources/Start_Hover.bmp");
		createButton(450, 350, 300, 80, "Resources/Options.bmp");
		createButton(450, 460, 300, 80, "Resources/Scores.bmp");
		createButton(450, 570, 300, 80, "Resources/Quit.bmp");
	}
	if (selectedButton == OPTIONS_BUTTON)
	{
		createButton(450, 240, 300, 80, "Resources/Start.bmp");
		createButton(450, 350, 300, 80, "Resources/Options_Hover.bmp");
		createButton(450, 460, 300, 80, "Resources/Scores.bmp");
		createButton(450, 570, 300, 80, "Resources/Quit.bmp");
	}
	if (selectedButton == SCORES_BUTTON)
	{
		createButton(450, 240, 300, 80, "Resources/Start.bmp");
		createButton(450, 350, 300, 80, "Resources/Options.bmp");
		createButton(450, 460, 300, 80, "Resources/Scores_Hover.bmp");
		createButton(450, 570, 300, 80, "Resources/Quit.bmp");
	}
	if (selectedButton == QUIT_BUTTON)
	{
		createButton(450, 240, 300, 80, "Resources/Start.bmp");
		createButton(450, 350, 300, 80, "Resources/Options.bmp");
		createButton(450, 460, 300, 80, "Resources/Scores.bmp");
		createButton(450, 570, 300, 80, "Resources/Quit_Hover.bmp");
	}
	SDL_RenderPresent(gRenderer);
}
