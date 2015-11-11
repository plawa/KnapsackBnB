
// ***********************************
//
// Author: Piotr Lawniczak (209775)
//		www.piotrlawniczak.eu
//
// ***********************************

#pragma once
#include "stdafx.h"

class TimeMeasure
{
public:
	TimeMeasure();
	~TimeMeasure();
	void startTimer();
	double stopTimer();
	double getCPUFrequency();
private:
	__int64 startTime;
	double CPUFreq;
};