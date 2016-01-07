// Borrow.cpp : 实现文件
//
#include "stdafx.h"
#include "BookManage.h"
#include "Borrow.h"
// Borrow

Borrow::Borrow()
{
	no=start_time=end_time=0;
}

Borrow::Borrow(const Borrow &borrow)
{
	no=borrow.no;
	start_time=borrow.start_time;
	end_time=borrow.end_time;
}

Borrow& Borrow::operator=(const Borrow &borrow)
{
	no=borrow.no;
	start_time=borrow.start_time;
	end_time=borrow.end_time;
	return *this;
}

Borrow::~Borrow()
{
}
