#pragma once
#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

bool SDL_StartUp();
bool loadMedia(std::string);
void close();
SDL_Texture* loadTexture(std::string path);
void createButton(short, short, short, short, std::string);

struct toggle {
	bool obstacleOn, powerUpsOn, points;
}toggle;

enum {
	START_BUTTON,
	OPTIONS_BUTTON,
	SCORES_BUTTON,
	QUIT_BUTTON,
};

enum {
	OBSTACLES_BUTTON,
	SPECIALS_BUTTON
};

enum {
	MENU,
	START,
	OPTIONS,
	SCORE
};

enum {
	SPLAYER_BUTTON=5,
	MPLAYER_BUTTON,
};

class LTexture
{
public:
	
	LTexture();
	~LTexture();
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	void free();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

TTF_Font *baseFont = NULL;
LTexture textTexture;
SDL_Window* pongWindow = NULL;
SDL_Surface* BG_Surface = NULL;
SDL_Surface* BG_Image = NULL;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* loadTexture(std::string path);

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(baseFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		SDL_FreeSurface(textSurface);
		return false;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			SDL_FreeSurface(textSurface);
			return false;
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
	return true;
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}


bool loadText(std::string text)
{
	baseFont = TTF_OpenFont("Resources/MATURASC.ttf", 36);

	if (baseFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		SDL_Color textColor = { 1000, 1000, 1000 };
		if (!textTexture.loadFromRenderedText(text, textColor))
		{
			printf("Failed to render text texture!\n");
			return false;
		}
	}

	return true;
}


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

void updateStartScreen(char selectedButton)
{
	SDL_RenderClear(gRenderer);
	SDL_RenderSetViewport(gRenderer, NULL);
	loadMedia("Resources/Menu_BG.bmp");
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	SDL_RenderPresent(gRenderer);

	if (selectedButton == SPLAYER_BUTTON)
	{
		createButton(410, 240, 370, 80, "Resources/SinglePlayer_Hover.bmp");
		createButton(400, 350, 400, 80, "Resources/Multiplayer.bmp");
	}
	if (selectedButton == MPLAYER_BUTTON)
	{
		createButton(410, 240, 370, 80, "Resources/SinglePlayer.bmp");
		createButton(400, 350, 400, 80, "Resources/Multiplayer_Hover.bmp");
	}

	SDL_RenderPresent(gRenderer);
}


void toggleSwitch(int row, bool toggled)
{
	if (toggled)
	{
		createButton(650, row, 100, 80, "Resources/On_Hover.bmp");
		createButton(770, row, 100, 80, "Resources/Off.bmp");
	}
	else
	{
		createButton(650, row, 100, 80, "Resources/On.bmp");
		createButton(770, row, 100, 80, "Resources/Off_Hover.bmp");
	}
	if (row == 240)
	{
		toggle.obstacleOn = toggled;
	}
	if (row == 340)
	{
		toggle.powerUpsOn = toggled;
	}
	SDL_RenderPresent(gRenderer);
}

void loadOptions()
{
	SDL_RenderClear(gRenderer);
	SDL_RenderSetViewport(gRenderer, NULL);
	loadMedia("Resources/Options_BG.bmp");
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	SDL_RenderPresent(gRenderer);

	createButton(330, 240, 300, 80, "Resources/Obstacles.bmp");
	createButton(320, 350, 300, 80, "Resources/Specials.bmp");

	SDL_RenderPresent(gRenderer);
}