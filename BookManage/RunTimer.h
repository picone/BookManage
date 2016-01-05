#pragma once
// RunTimer
class RunTimer
{
public:
	RunTimer();
	virtual ~RunTimer();
	void end();
	float get_time();
	void get_str_time(CString &time);
private:
	LARGE_INTEGER start_time;
	LARGE_INTEGER end_time;
};
