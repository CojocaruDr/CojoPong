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
			bool  delay = 1;
			int currentRow = 240;
			SDL_Event e;
			char currentButton = START_BUTTON, currentMenu = MENU;

			while (GAME)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						GAME = false;
					}
					else
						if (e.type == SDL_KEYDOWN && currentMenu == MENU)
						{
							SDL_RenderPresent(gRenderer);

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
								if (currentButton == QUIT_BUTTON)
									GAME = false;
								if (currentButton == SCORES_BUTTON)
								{
									currentMenu = SCORE;
									openScores();
								}
								if (currentButton == START_BUTTON)
								{
									currentMenu = START;
									currentButton = MPLAYER_BUTTON;
									updateStartScreen(MPLAYER_BUTTON);
									delay = 1;
								}
								if (currentButton == OPTIONS_BUTTON)
								{
									currentMenu = OPTIONS;
									currentButton = OBSTACLES_BUTTON;
									loadOptions();
									toggleSwitch(240, toggle.obstacleOn);
									toggleSwitch(340, toggle.powerUpsOn);
								}
							}
						}
						if (e.type == SDL_KEYDOWN && currentMenu == SCORE)
							{
								if (e.key.keysym.sym == SDLK_BACKSPACE)
								{
									currentMenu = MENU;
									currentButton = SCORES_BUTTON;
									updateScreen(SCORES_BUTTON);
								}

							}

						if (e.type == SDL_KEYDOWN && currentMenu == START)
						{
;							if (e.key.keysym.sym == SDLK_DOWN)
							{
								if (currentButton == SPLAYER_BUTTON)
								{
									currentButton++;
									updateStartScreen(MPLAYER_BUTTON);
								}
							}
							if (e.key.keysym.sym == SDLK_UP)
							{
								if (currentButton == MPLAYER_BUTTON)
								{
									currentButton--;
									updateStartScreen(SPLAYER_BUTTON);
									
								}
							}
							if (e.key.keysym.sym == SDLK_BACKSPACE)
							{
								currentMenu = MENU;
								currentButton = START_BUTTON;
								updateScreen(START_BUTTON);
							}

							if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN)
							{
								if (delay == 0)
								{
									if (currentButton == MPLAYER_BUTTON)
									{
										multiPlayer();
									}
								}
								else
									delay = 0;
							}
							
						}

						if (e.type = SDL_KEYDOWN && currentMenu == OPTIONS)
						{
							if (e.key.keysym.sym == SDLK_DOWN)
							{
								if (currentButton < SPECIALS_BUTTON)
								{
									currentButton++;
									currentRow += 100;
								}
							}
							if (e.key.keysym.sym == SDLK_UP)
							{
								if (currentButton > OBSTACLES_BUTTON)
								{
									currentButton--;
									currentRow -= 100;
								}
							}
							if (e.key.keysym.sym == SDLK_RIGHT)
							{
								loadOptions();
								toggleSwitch(currentRow, false);
								if (currentRow == 240)
								{
									toggleSwitch(340, toggle.powerUpsOn);
								}
								else
								{

									toggleSwitch(240, toggle.obstacleOn);
								}
							}
							if (e.key.keysym.sym == SDLK_LEFT)
							{
								loadOptions();
								toggleSwitch(currentRow, true);
								if (currentRow == 240)
								{
									toggleSwitch(340, toggle.powerUpsOn);
								}
								else
								{

									toggleSwitch(240, toggle.obstacleOn);
								}
								
							}
							if (e.key.keysym.sym == SDLK_BACKSPACE)
							{
								currentMenu = MENU;
								currentButton = OPTIONS_BUTTON;
								updateScreen(OPTIONS_BUTTON);
							}
						}
						
				}
			}
		}
	}

	close();

	return 0;
}
