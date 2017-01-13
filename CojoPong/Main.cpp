#include "Scores.h"
#include "singleplayer.h"
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
			

			while (GAME)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						GAME = false;
					}

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
							if (currentButton == QUIT_BUTTON)
							{
								GAME = false;
								freeMedia();
							}
							if (currentButton == SCORES_BUTTON)
							{
								currentMenu = SCORE;
								freeMedia();
								openScores();
							}
							if (currentButton == START_BUTTON)
							{
								currentMenu = START;
								currentButton = MPLAYER_BUTTON;
								freeMedia();
								updateStartScreen(MPLAYER_BUTTON);
								delay = 1;
							}
							if (currentButton == OPTIONS_BUTTON)
							{
								currentMenu = OPTIONS;
								currentButton = OBSTACLES_BUTTON;
								freeMedia();
								loadOptions(OBSTACLES_BUTTON);
								toggleSwitch(240, toggle.obstacleOn);
								toggleSwitch(340, toggle.powerUpsOn);
								toggleGames(toggle.points);
								displayName(630, 550, playerOneName, currentButton);
							}
						}
					}

					if (e.type == SDL_KEYDOWN && currentMenu == SCORE)
					{
						if (e.key.keysym.sym == SDLK_BACKSPACE)
						{
							currentMenu = MENU;
							currentButton = SCORES_BUTTON;
							freeMedia();
							updateScreen(SCORES_BUTTON);
						}

					}

					if (e.type == SDL_KEYDOWN && currentMenu == START)
					{
						if (e.key.keysym.sym == SDLK_DOWN)
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
							freeMedia();
							updateScreen(START_BUTTON);
						}

						if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN)
						{
							if (delay == 0)
							{
								if (currentButton == MPLAYER_BUTTON)
								{
									freeMedia();
									multiPlayer();
								}

							}
							else
								delay = 0;

							if (currentButton == SPLAYER_BUTTON)
							{
								currentButton = BEGINNER_BUTTON;
								currentMenu = SPLAYER;
								delay = 1;
								freeMedia();
								loadSPlayer(currentButton);
							}
						}

					}

					if (e.type == SDL_KEYDOWN && currentMenu == OPTIONS)
					{

						if (e.key.keysym.sym == SDLK_DOWN)
						{
							
							if (currentButton < PLAYER2_BUTTON)
							{
							
								currentButton++;
								loadOptions(currentButton);
								toggleSwitch(240, toggle.obstacleOn);
								toggleSwitch(340, toggle.powerUpsOn);
								toggleGames(toggle.points);
								displayName(630, 550, playerOneName, currentButton);
							}
							
						}

						if (e.key.keysym.sym == SDLK_UP)
						{
							if (currentButton > OBSTACLES_BUTTON)
							{
							
								currentButton--;
								loadOptions(currentButton);
								toggleSwitch(240, toggle.obstacleOn);
								toggleSwitch(340, toggle.powerUpsOn);
								toggleGames(toggle.points);
								displayName(630, 550, playerOneName, currentButton);
							}
						}

						if (e.key.keysym.sym == SDLK_RIGHT)
						{
							if (currentButton == 10)
							{
								loadOptions(OBSTACLES_BUTTON);
								toggleSwitch(240, false);
								toggleSwitch(340, toggle.powerUpsOn);
								toggleGames(toggle.points);
								displayName(630, 550, playerOneName, currentButton);

							}
							else
								if (currentButton == 11)
								{
									loadOptions(SPECIALS_BUTTON);
									toggleSwitch(340, false);
									toggleSwitch(240, toggle.obstacleOn);
									toggleGames(toggle.points);
									displayName(630, 550, playerOneName, currentButton);
								}
								else {
									loadOptions(GAMES_BUTTON);
									toggleSwitch(240, toggle.obstacleOn);
									toggleSwitch(340, toggle.powerUpsOn);
									toggleGames(false);
									displayName(630, 550, playerOneName, currentButton);
								}
						}
						if (e.key.keysym.sym == SDLK_LEFT)
						{

							if (currentButton == 10)
							{
								loadOptions(OBSTACLES_BUTTON);
								toggleSwitch(240, true);
								toggleSwitch(340, toggle.powerUpsOn);
								toggleGames(toggle.points);
								displayName(630, 550, playerOneName, currentButton);
							}
							else
								if (currentButton == 11)
								{
									loadOptions(SPECIALS_BUTTON);
									toggleSwitch(340, true);
									toggleSwitch(240, toggle.obstacleOn);
									toggleGames(toggle.points);
									displayName(630, 550, playerOneName, currentButton);
								}
								else {
									loadOptions(GAMES_BUTTON);
									toggleSwitch(240, toggle.obstacleOn);
									toggleSwitch(340, toggle.powerUpsOn);
									toggleGames(true);
									displayName(630, 550, playerOneName, currentButton);
								}

						}
						if (e.key.keysym.sym == SDLK_BACKSPACE)
						{
							currentMenu = MENU;
							currentButton = OPTIONS_BUTTON;
							currentRow = 240;
							freeMedia();
							updateScreen(OPTIONS_BUTTON);
						}

						if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
						{
							delay = 0;
							if (currentButton == PLAYER1_BUTTON)
							{
								if (delay == 0)
								{

									std::getline(cin, playerOneName);
									delay = 1;
									while (checkName(playerOneName) != "OK")
									{

										cout << checkName(playerOneName) << endl;
										std::getline(cin, playerOneName);
										
									}
									delay = 1;
									displayName(630, 550, playerOneName, currentButton);
								}
								else delay = 0;
							}


							if (currentButton == PLAYER2_BUTTON)
							{
								if (delay == 0)
								{


									std::getline(cin, playerTwoName);
									delay = 1;
									while (checkName(playerTwoName) != "OK")
									{

										cout << checkName(playerTwoName) << endl;
										std::getline(cin, playerTwoName);
										
									}
									delay = 1;
									displayName(630, 650, playerTwoName, currentButton);
								}
								else delay = 0;
							}

						}
					}

					if (e.type == SDL_KEYDOWN && currentMenu == SPLAYER)
					{
						if (e.key.keysym.sym == SDLK_DOWN)
						{
							if (currentButton < EXPERT_BUTTON)
							{
								currentButton++;
								loadSPlayer(currentButton);
							}
						}
						if (e.key.keysym.sym == SDLK_UP)
						{
							if (currentButton > BEGINNER_BUTTON)
							{
								currentButton--;
								loadSPlayer(currentButton);
							}
						}

						if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
						{
							if (delay == 0)
							{
								if (currentButton == BEGINNER_BUTTON)
								{
									toggle.AI_Difficulty = 0;
									singlePlayer();
								}
								else
									if (currentButton == INTERMEDIATE_BUTTON)
									{
										toggle.AI_Difficulty = 1;
										singlePlayer();
									}
									else
									{
										toggle.AI_Difficulty = 2;
										singlePlayer();
									}

							}
							else delay = 0;
						}
						
						if (e.key.keysym.sym == SDLK_BACKSPACE)
						{
							currentMenu = START;
							currentButton = SPLAYER_BUTTON;
							freeMedia();
							updateStartScreen(SPLAYER_BUTTON);
						}

					}
				}
			}
		}
	}

	close();

	return 0;
}
