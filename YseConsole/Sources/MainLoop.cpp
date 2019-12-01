#ifdef _DEBUG
#include <iostream>
#endif // DEBUG

#include "MainLoop.h"
#include <cfloat>
#include <thread>

#include "Configuration.h"

using namespace std;



bool UpdateDelegate::Register(IUpdateEntity* ToRegister)
{
#ifdef _DEBUG
	cout << __FUNCTION__ << "Param's key : " << &ToRegister << "\n";
#endif // _DEBUG

	/* return false if key is already existed
	 * object's address is key */
	if (Delegate.find((long long)&ToRegister) != Delegate.end())
		return false;

	/* register IUpdateEntity */
	Delegate.insert(std::pair<long long, IUpdateEntity*>((long long)ToRegister, ToRegister));
	return true;
}

bool UpdateDelegate::UnRegister(const IUpdateEntity* ToUnregister)
{
	/* true if it removes elements, otherwise false */
	return static_cast<bool>(Delegate.erase((long long)ToUnregister));
}

void UpdateDelegate::Broadcast(float DeltaTime)
{
#ifdef _DEBUG
	cout << "Delegate size : " << Delegate.size() << "\n";
#endif // _DEBUG

	/* call all update entity */
	for (auto& it : Delegate)
	{
		it.second->Update(DeltaTime);
	}
}






void MainLoop::Loop()
{
	/* variable tick count */
	unsigned int TickCount = 1;

	while (bLooping)
	{
		chrono::time_point TP1 = chrono::high_resolution_clock::now();
		/* core function */
		Update((float)(FramePeriod * TickCount) / 10e+5);
		chrono::time_point TP2 = chrono::high_resolution_clock::now();

		long long ElapsedTime = chrono::duration_cast<std::chrono::microseconds>(TP2 - TP1).count();
		long long SleepTime = FramePeriod - (ElapsedTime % FramePeriod);
		TickCount = static_cast<unsigned int>((ElapsedTime / FramePeriod) + 1);

		/* make cpu idle for the remainder of one frame */
		this_thread::sleep_for(chrono::microseconds(SleepTime));
	}
}

void MainLoop::SetFrameRate(float InFrameRate)
{
	FrameRate = InFrameRate;
	SetFramePeriod();
}

void MainLoop::Update(float DeltaTime)
{
#ifdef _DEBUG
	cout << "DeltaTime : " << DeltaTime << "\n";
#endif // _DEBUG

	pUpdateDelegate.get()->Broadcast(DeltaTime);
}

void MainLoop::SetFramePeriod()
{
	/* escape if frame rate is not valid */
	if (FrameRate <= 0.f)
		return;

	/* get frame period (microseconds) */
	float Period = 1 / FrameRate;
	if (Period < FLT_EPSILON)
		SetFrameRate(APP::DefaultFrameRate);
	else
		FramePeriod = Period * 10e+5;
}