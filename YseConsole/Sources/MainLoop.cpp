#ifdef _DEBUG
#include <iostream>
#endif // DEBUG

#include "MainLoop.h"
#include <cfloat>
#include <thread>

#include "Configuration.h"

using namespace std;




void MainLoop::Loop()
{
	/* variable tick count */
	unsigned int TickCount = 1;

	while (bLooping)
	{
		chrono::time_point TP1 = chrono::high_resolution_clock::now();
		Update((FramePeriod * TickCount) / 1000000);
		chrono::time_point TP2 = chrono::high_resolution_clock::now();

		long long ElapsedTime = chrono::duration_cast<std::chrono::microseconds>(TP2 - TP1).count();
		long long SleepTime = FramePeriod - (ElapsedTime % FramePeriod);
		TickCount = static_cast<unsigned int>((ElapsedTime / FramePeriod) + 1);
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
		FramePeriod = static_cast<long long>(Period) * 1000000;
}
