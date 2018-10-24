#include "stdafx.h"
#include "safe.h"


safe::safe()
{
}


safe::~safe()
{
}

void safe::chkCN(int CN[])
{
	if (CN[0] == CN[1] || CN[0] == CN[2] || CN[0] == CN[3] || CN[1] == CN[2] || CN[1] == CN[3] || CN[2] == CN[3]) {
		safeb = false;
	}
	else {
		safeb = true;
	}
}

bool safe::reCNSafe()
{
	return safeb;
}
