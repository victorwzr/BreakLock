#pragma once
class HashFunction
{
public:
	HashFunction();
	~HashFunction();
	void HashHN(int HN[], int HNkey[]);
	int* getHN();
	void HashCN(int CN[], int CNkey[]);
	int* getCN();
	int getCNsum();
private:
	int *THN, *TCN;
	int CN, LN;
	int sum;
};

