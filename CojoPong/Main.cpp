#include <SDL2/SDL.h>
#include "MenuFunctions.h"

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
			char currentButton = START_BUTTON;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else
						if (e.type == SDL_KEYDOWN)
						{
							if (e.key.keysym.sym == SDLK_UP)
							{
								if (currentButton > 0)
									currentButton--;
							}
							if (e.key.keysym.sym == SDLK_DOWN)
							{
								if(currentButton<3)
								currentButton++;
							}
							updateScreen(currentButton);
						}
				}
			}

		}
	}

	close();

	return 0;
}
