#pragma once 

#include <functional> 

class Timer
{
public:
	void Update( const double delta );
	void Start( const double duration );

	inline void SetCallback( std::function<void()> callback_in ) { callback = callback_in; }

private:
	std::function<void()> callback;
	double timeLeft = 0.0;
	bool isRunning = false;
};