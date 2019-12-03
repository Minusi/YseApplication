#pragma once
#include <map>
#include <memory>
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
	virtual bool Update(float DeltaTime) = 0;
};





/*
 *	UpdateDelegate imitiates unreal engine 4's multicast delegate.
 *	multicast means delegate can contain and broadcast multiple functions.
 */
class UpdateDelegate
{
public:
	/* default constructor */
	UpdateDelegate() = default;
	~UpdateDelegate() = default;

	/* register param's update function to delegate 
	 * class type must be derived from IUpdateEntity 
	 *
	 * return true if register process is successed, otherwise false */
	bool Register(IUpdateEntity* ToRegister);

	/* unregister update function from delegate 
	 * return true if unregister is successed, otherwise false */
	bool UnRegister(const IUpdateEntity* ToUnregister);

	/* Broadcast all of registered class */
	void Broadcast(float DeltaTime);

private:
	std::map<long long, IUpdateEntity*> Delegate;
};





/*
 *	MainLoop represents Application's loop.
 *	it supports variable frame rate.
 */
class MainLoop final
{
public:
	/* constructor and destructor */
	MainLoop();
	~MainLoop() = default;

	/* start apllication main loop */
	void Loop();

private:
	void Update(float DeltaTime);



public:
	/* setting frame rate */
	void SetFrameRate(float InFrameRate);

private:
	/* set frame period */
	void SetFramePeriod();

public:
	/* getter function */
	inline UpdateDelegate* OnUpdateDelegate() const
	{
		return pUpdateDelegate.get();
	}



private:
	/* if MainLoop can be looping */
	bool bLooping;

	/* Frame per seconds */
	float FrameRate;

	/* Period of single frame (microseconds) */
	long long FramePeriod;

private:
	/* update delegate */
	std::unique_ptr<UpdateDelegate> pUpdateDelegate;
};