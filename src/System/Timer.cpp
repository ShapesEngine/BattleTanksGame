#include "Timer.h"

void Timer::Update( const double delta )
{
	if( isRunning )
	{
		timeLeft -= delta;
		if( timeLeft <= 0.0 )
		{
			isRunning = false;
			callback();
		}
	}
}

void Timer::Start( const double duration )
{
	timeLeft = duration;
	isRunning = true;
}
