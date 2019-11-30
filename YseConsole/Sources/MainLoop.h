#pragma once
#include <chrono>
#include "Configuration.h"



/*
 *	UpdateEntity is interface for updating in main loop.
 *	All entity want to update must inherit this interface
 */
class IUpdateEntity
{
public:
	/* updates entity. return true if entity want to 
	update next frame, otherwise false */
	virtual bool Update() = 0;
};





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

	/* start apllication main loop */
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