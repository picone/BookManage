#pragma once
// RunTimer
class RunTimer
{
public:
	RunTimer();
	virtual ~RunTimer();
	void end();
	float get_time();
private:
	LARGE_INTEGER start_time;
	LARGE_INTEGER end_time;
};
