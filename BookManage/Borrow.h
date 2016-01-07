#pragma once
// Borrow
class Borrow:public CObject
{
public:
	Borrow();
	Borrow(const Borrow &borrow);
	Borrow& operator=(const Borrow &borrow);
	virtual ~Borrow();
	UINT no;
	int start_time;
	int end_time;
};
