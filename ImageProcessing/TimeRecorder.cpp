#include "stdafx.h"
#include "TimeRecorder.h"


TimeRecorder::TimeRecorder()
	:t_start(std::chrono::high_resolution_clock::now()),
	t_end(std::chrono::high_resolution_clock::now())
{
}


TimeRecorder::~TimeRecorder()
{
}

std::chrono::high_resolution_clock::time_point TimeRecorder::start()
{
	t_start = std::chrono::high_resolution_clock::now();

	return t_start;
}

std::chrono::high_resolution_clock::time_point TimeRecorder::end()
{
	t_end = std::chrono::high_resolution_clock::now();

	return t_end;
}

long long TimeRecorder::getPeriod()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
}

std::wstring TimeRecorder::getPeriodUnit()
{
	return L"milliseconds";
}
