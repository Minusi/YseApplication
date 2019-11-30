#pragma once
#include <chrono>
#include "Configuration.h"



/*
 *	MainLoop represents Application's loop.
 *	it supports variable frame rate.
 */
class MainLoop final
{
public:
	/* default constructor */
	MainLoop()
	: bLooping(true)
	, FrameRate(APP::DefaultFrameRate)
	{
		SetFramePeriod();
	}

	/* Start Loop */
	void Loop();

	/* setting frame rate */
	void SetFrameRate(float InFrameRate);

private:
	void Update(float DeltaTime);

private:
	/* set frame period */
	void SetFramePeriod();



private:
	/* if MainLoop can be looping */
	bool bLooping;

	/* Frame per seconds */
	float FrameRate;

	/* Period of single frame (microseconds) */
	long long FramePeriod;
};