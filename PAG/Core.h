#pragma once
#include <Windows.h>
#include "Window.h"

class Core
{
private:
	Window *window;
	bool game_is_running;
	const int TICKS_PER_SECOND = 50;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 10;

	void updateGame();
public:
	Core();
	~Core();
};
