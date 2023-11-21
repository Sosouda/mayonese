	#include "Game.h"

	Game *game = nullptr;

	int main(int argc, char *argv[])
	{

		const int FPS = 60;
		const int frameDelay = 1000 / FPS;

		Uint32 frameStart;
		int frameTime;

		game = new Game();
		game->init("GameWindow", 900, 500, false);

	
		while (game->running())
		{
			game->handleEvents();
			game->render();
			if (!game->isPaused()) {
				game->update();
			}

			frameStart = SDL_GetTicks();

		

			frameTime = SDL_GetTicks() - frameStart;
		
			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}

		game->clean();
		return 0;
	}