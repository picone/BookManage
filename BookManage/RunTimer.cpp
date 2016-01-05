// RunTimer.cpp : 实现文件
//
#include "stdafx.h"
#include "BookManage.h"
#include "RunTimer.h"

RunTimer::RunTimer()
{
	QueryPerformanceCounter(&start_time);
}

RunTimer::~RunTimer()
{

}

void RunTimer::end()
{
	QueryPerformanceCounter(&end_time);
}

float RunTimer::get_time()
{
	LARGE_INTEGER freq,run_count;
	QueryPerformanceFrequency(&freq);
	run_count.QuadPart=end_time.QuadPart-start_time.QuadPart;
	return (float)run_count.QuadPart/(float)freq.QuadPart;
}
