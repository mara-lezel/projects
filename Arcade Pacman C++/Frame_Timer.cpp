#include "Frame_Timer.h"
#include <SDL.h>

//To avoid starting the timer at class initialization
//Have to manually start the timer
void FrameTimer::start()
{
	reset();
}

//Reset and start tracking from current clock time
void FrameTimer::reset()
{
	start_ticks_ = SDL_GetTicks();
	elapsed_ticks_ = 0;
	delta_time_ = 0.0f;
}

//Get time elapsed between frames and convert to seconds
void FrameTimer::update()
{
	elapsed_ticks_ = SDL_GetTicks() - start_ticks_;
	delta_time_ = elapsed_ticks_ * 0.001f;
}


float FrameTimer::getDeltaTime() const
{
	return delta_time_;
}