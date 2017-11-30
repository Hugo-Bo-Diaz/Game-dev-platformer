// ----------------------------------------------------
// j1Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "j1Timer.h"
#include "SDL\include\SDL_timer.h"

// ---------------------------------------------
j1Timer::j1Timer()
{
	Start();
}

// ---------------------------------------------
void j1Timer::Start()
{
	started_at = SDL_GetTicks();
}

// ---------------------------------------------
uint32 j1Timer::Read() const
{
	return SDL_GetTicks() - started_at - time_paused;
}

// ---------------------------------------------
float j1Timer::ReadSec() const
{
	return float(SDL_GetTicks() - started_at - time_paused) / 1000.0f;
}

// ---------------------------------------------
void j1Timer::Pause()
{
	if (!paused)
	{
		paused_at = SDL_GetTicks();
		paused = true;
	}
}

// ---------------------------------------------
void j1Timer::Resume()
{
	if (paused)
	{
		resumed_at = SDL_GetTicks();
		time_paused += resumed_at - paused_at;
		paused = false;
	}
}
