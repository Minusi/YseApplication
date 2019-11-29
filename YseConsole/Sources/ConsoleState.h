#pragma once



/* 
 *	IConsoleStatus represents console's inner state.
 *	To be precise, it is an interface to the console state.
 *	inner state can be changed by user's input.
 *
 *	for example, if console show main menu, and user
 *	want to play any musics, console inner state need to be
 *	changed other state("play state").
 */
class IConsoleStatus
{
public:
	/* Interface to update console state */
	virtual void Update() = 0;
};