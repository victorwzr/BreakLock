#pragma once
#include <vector>

using namespace std;

struct Locks {
	int index[4];//Root
	int A[4];    //LN0
	int B[4];    //LN1
	int C[4];    //LN2
	int D[4];    //LN3
	int E[4];    //LN4
};

class Lock
{
public:
	Lock();
	~Lock();
	void setLock();
	void setPHF();
	void SplitString(const string& s, vector<string>& v, const string& c);
	int* rePHF();
	void setHN();
	void runCN();



private:

	string line;
	string culine;
	vector<string> vec;
	vector<int> LN0;
	vector<int> LN1;
	vector<int> LN2;
	vector<int> LN3;
	vector<int> LN4;
	vector<int> Root;
	vector<int> vec_tmp;
	vector<string> LINE;
	vector<Locks> lock;
	vector<int*> HN0, HN1, HN2, HN3, HN4;
	int UHF[10000][4];
	int LHF[10000][4];
	int ULHF[4];
	int PHF[4];
	int temp;
	int *HN0temp, *HN1temp, *HN2temp, *HN3temp, *HN4temp, *safetemp;
	bool safeCN;
	int chkcounter = 0;   //for chk
};

