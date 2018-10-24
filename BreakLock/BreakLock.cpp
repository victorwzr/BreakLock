// BreakLock.cpp : Defines the entry point for the console application.
//Zhaoran Wang 150382450 Program enter point

#include "stdafx.h"
#include "Lock.h"
#include <iostream>

using namespace std;

Lock *l = new Lock();

int main()
{
	l->setLock();
	l->setPHF();
	l->setHN();
	l->runCN();
    return 0;
}

