#pragma once
#include <chrono>
#include <string>

class TimeRecorder
{
private:
	std::chrono::high_resolution_clock::time_point t_start;
	std::chrono::high_resolution_clock::time_point t_end;
public:
	TimeRecorder();
	~TimeRecorder();

	std::chrono::high_resolution_clock::time_point start();
	std::chrono::high_resolution_clock::time_point end();
	long long getPeriod();
	std::wstring getPeriodUnit();
};

