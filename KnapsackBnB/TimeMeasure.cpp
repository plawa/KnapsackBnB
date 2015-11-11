
// ***********************************
//
// Author: Piotr Lawniczak (209775)
//		www.piotrlawniczak.eu
//
// ***********************************

#include "TimeMeasure.h"
#include "stdafx.h"
#include <Windows.h>

TimeMeasure::TimeMeasure()
{
	startTime = 0;
	CPUFreq = 0.0;
}

TimeMeasure::~TimeMeasure()
{
}

void TimeMeasure::startTimer()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		printf("Counter error!");
	CPUFreq = double(li.QuadPart);
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&li);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	startTime = li.QuadPart;
}
double TimeMeasure::stopTimer()
{
	LARGE_INTEGER li;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&li);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return 1000*( (double)(li.QuadPart - startTime) / CPUFreq ); //multiplied by 1000, for gain [ms] unit
}
double TimeMeasure::getCPUFrequency(){
	return CPUFreq;
}