#pragma once
class safe
{
public:
	safe();
	~safe();
	void chkCN(int CN[]);
	bool reCNSafe();
private:
	bool safeb;
};


