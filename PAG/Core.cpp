#include "Core.h"

Core::Core()
{
	DWORD next_game_tick = GetTickCount();
	int loops;

	game_is_running = true;
	while (game_is_running) {
		loops = 0;
		while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
			updateGame();
			next_game_tick += SKIP_TICKS;
			loops++;
		}
		window->renderGame();
	}
}

void Core::updateGame()
{
	//TODO
}

Core::~Core()
{
}
