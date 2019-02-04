#pragma once
#include <iostream>

#include "GL/glut.h"

#pragma warning(push)
#pragma warning(disable : 244)
/*
 * timer class
 * - this lets us keep track of the elapsed time
 *   in our program easily so we can use it in things
 *   like physics calculations 
 */
class Timer
{
public:
	Timer()
	{
		previousTime = glutGet(GLUT_ELAPSED_TIME);
		this->tick();
	}

	~Timer();

	// update the timer clock
	float tick()
	{
		currentTime = glutGet(GLUT_ELAPSED_TIME);
		elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		return elapsedTime;
	}

	// delta time in milliseconds 
	float getElapsedTimeMS()
	{
		return elapsedTime;
	}

	// delta time in seconds
	float getElapsedTimeSeconds()
	{
		return elapsedTime / 1000.f;
	}

	float getCurrentTime()
	{
		return currentTime;
	}

private:
	float currentTime, previousTime, elapsedTime;
};

#pragma warning(pop)