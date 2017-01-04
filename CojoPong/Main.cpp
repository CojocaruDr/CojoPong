#include "MenuFunctions.h"
#include "Scores.h"
#include "multiplayer.h"
int main(int argc, char* args[])
{
	if (!SDL_StartUp())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia("Resources/Menu_BG.bmp"))
		{
			printf("Failed to load media!\n");
		}
		else
		{

			updateScreen(START_BUTTON);

			bool quit = false;
			SDL_Event e;
			char currentButton = START_BUTTON, currentMenu = MENU;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else
						if (e.type == SDL_KEYDOWN && currentMenu == MENU)
						{
							if (e.key.keysym.sym == SDLK_UP)
							{
								if (currentButton > 0)
									currentButton--;
								updateScreen(currentButton);
							}
							if (e.key.keysym.sym == SDLK_DOWN)
							{
								if (currentButton < 3)
									currentButton++;
								updateScreen(currentButton);
							}
							if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN)
							{
								if (currentButton == 3)
									quit = true;
								if (currentButton == 2)
								{
									currentMenu = SCORE;
									openScores();
								}
								if (currentButton == 0)
								{
									SDL_RenderClear(gRenderer);
									currentMenu = START;
									multiPlayer();
								}
							}
						}
						if (e.type == SDL_KEYDOWN && currentMenu == SCORE)
							{
								if (e.key.keysym.sym == SDLK_BACKSPACE)
								{
									currentMenu = MENU;
									currentButton = START_BUTTON;
									updateScreen(START_BUTTON);
								}

							}
						
				}
			}
		}
	}

	close();

	return 0;
}
