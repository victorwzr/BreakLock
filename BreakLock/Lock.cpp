#include "stdafx.h"
#include "sstream"
#include "Lock.h"
#include<iostream>
#include<string>
#include "HashFunction.h"
#include "safe.h"
#include<fstream>

HashFunction *hfun = new HashFunction();
safe *sf = new safe();


Lock::Lock()
{
}


Lock::~Lock()
{
}

void Lock::SplitString(const string& s, vector<string>& v, const string& c)              //split function
{ 
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}


void Lock::setLock()
{
	ifstream infile;
	infile.open("locked-safe.txt");                //file stream
	while (getline(infile, line)) {
		LINE.push_back(line);
	}
	std::stringstream s;
	for (auto iter = LINE.cbegin(); iter != LINE.cend(); iter++) {
		culine = (*iter);                                   //input from file into string vector as line
		vec.clear();
		if (culine == "") {                     //split number and id and check id to input number into vector to storage

		}
		else {
			SplitString(culine, vec, " ");
			if (vec[0] == "ROOT:") {
				s << vec[1];
				s >> temp;
				Root.push_back(temp);
				s.clear();
			}
			else {
				if (vec[0] == "LN0:") {
					s << vec[1];
					s >> temp;
					LN0.push_back(temp);
					s.clear();
				}
				else {
					if (vec[0] == "LN1:") {
						s << vec[1];
						s >> temp;
						LN1.push_back(temp);
						s.clear();
					}
					else {
						if (vec[0] == "LN2:") {
							s << vec[1];
							s >> temp;
							LN2.push_back(temp);
							s.clear();
						}
						else {
							if (vec[0] == "LN3:") {
								s << vec[1];
								s >> temp;
								LN3.push_back(temp);
								s.clear();
							}
							else {
								if (vec[0] == "LN4:") {
									s << vec[1];
									s >> temp;
									LN4.push_back(temp);
									s.clear();
								}
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < 100; i++) {                                //split digit and pass to 100 locks data type in vector
		lock.push_back(Locks());
		lock[i].index[0] = Root[i] / 1000;
		lock[i].index[1] = Root[i] / 100 - lock[i].index[0] * 10;
		lock[i].index[2] = Root[i] / 10 - lock[i].index[0] * 100 - lock[i].index[1] * 10;
		lock[i].index[3] = Root[i] - lock[i].index[0] * 1000 - lock[i].index[1] * 100 - lock[i].index[2] * 10;
		lock[i].A[0] = LN0[i] / 1000;
		lock[i].A[1] = LN0[i] / 100 - lock[i].A[0] * 10;
		lock[i].A[2]= LN0[i] / 10 - lock[i].A[0] * 100 - lock[i].A[1] * 10;
		lock[i].A[3] = LN0[i] - lock[i].A[0] * 1000 - lock[i].A[1] * 100 - lock[i].A[2] * 10;
		lock[i].B[0] = LN1[i] / 1000;
		lock[i].B[1] = LN1[i] / 100 - lock[i].B[0] * 10;
		lock[i].B[2] = LN1[i] / 10 - lock[i].B[0] * 100 - lock[i].B[1] * 10;
		lock[i].B[3] = LN1[i] - lock[i].B[0] * 1000 - lock[i].B[1] * 100 - lock[i].B[2] * 10;
		lock[i].C[0] = LN2[i] / 1000;
		lock[i].C[1] = LN2[i] / 100 - lock[i].C[0] * 10;
		lock[i].C[2] = LN2[i] / 10 - lock[i].C[0] * 100 - lock[i].C[1] * 10;
		lock[i].C[3] = LN2[i] - lock[i].C[0] * 1000 - lock[i].C[1] * 100 - lock[i].C[2] * 10;
		lock[i].D[0] = LN3[i] / 1000;
		lock[i].D[1] = LN3[i] / 100 - lock[i].D[0] * 10;
		lock[i].D[2] = LN3[i] / 10 - lock[i].D[0] * 100 - lock[i].D[1] * 10;
		lock[i].D[3] = LN3[i] - lock[i].D[0] * 1000 - lock[i].D[1] * 100 - lock[i].D[2] * 10;
		lock[i].E[0] = LN4[i] / 1000;
		lock[i].E[1] = LN4[i] / 100 - lock[i].E[0] * 10;
		lock[i].E[2] = LN4[i] / 10 - lock[i].E[0] * 100 - lock[i].E[1] * 10;
		lock[i].E[3] = LN4[i] - lock[i].E[0] * 1000 - lock[i].E[1] * 100 - lock[i].E[2] * 10;
	}
	Root.clear();               //release the vector
	LN0.clear();
	LN1.clear();
	LN2.clear();
	LN3.clear();
	LN4.clear();
}

void Lock::setPHF()
{
	PHF[0] = lock[0].B[0] - lock[0].A[0] - lock[0].A[0] + lock[0].index[0];           //PHF digit set
	PHF[1] = lock[0].B[1] - lock[0].A[1] - lock[0].A[1] + lock[0].index[1];
	PHF[2] = lock[0].B[2] - lock[0].A[2] - lock[0].A[2] + lock[0].index[2];
	PHF[3] = lock[0].B[3] - lock[0].A[3] - lock[0].A[3] + lock[0].index[3];
	for (int i = 0; i < 4; i++) {
		if (PHF[i] >= 10) {
			PHF[i] = (PHF[i] - 10);
		}
		if (PHF[i] < 0)
			PHF[i] = PHF[i] + 10;
		cout << PHF[i] << endl;
	}
}

int* Lock::rePHF()
{
	return PHF;
}

void Lock::setHN()
{
	for (int i = 0; i < 100; i++) {
		hfun->HashHN(lock[i].A, PHF);
		HN0.push_back(hfun->getHN());
		//cout << hfun->getHN() << endl;
		hfun->HashHN(lock[i].B, PHF);
		HN1.push_back(hfun->getHN());
		hfun->HashHN(lock[i].C, PHF);
		HN2.push_back(hfun->getHN());
		hfun->HashHN(lock[i].D, PHF);
		HN3.push_back(hfun->getHN());
		hfun->HashHN(lock[i].E, PHF);
		HN4.push_back(hfun->getHN());
	}
	/*for (int i = 0; i < HN0.size(); i++) {               //Output check
		HN0temp = HN0.at(i);
		HN1temp = HN1.at(i);
		HN2temp = HN2.at(i); 
		HN3temp = HN3.at(i);
		HN4temp = HN4.at(i);
		cout << "HN0 " << HN0temp[0] ;
		cout << HN0temp[1] ;
		cout << HN0temp[2] ;
		cout << HN0temp[3] << endl;
		cout << "HN1 " << HN1temp[0];
		cout << HN1temp[1];
		cout << HN1temp[2];
		cout << HN1temp[3] << endl;
		cout << "HN2 " << HN2temp[0];
		cout << HN2temp[1];
		cout << HN2temp[2];
		cout << HN2temp[3] << endl;
		cout << "HN3 " << HN3temp[0];
		cout << HN3temp[1];
		cout << HN3temp[2];
		cout << HN3temp[3] << endl;
		cout << "HN4 " << HN4temp[0];
		cout << HN4temp[1];
		cout << HN4temp[2];
		cout << HN4temp[3] << endl;
	}*/
}

void Lock::runCN()
{
	ULHF[0] = lock[0].A[0] - lock[0].index[0] - PHF[0];
	ULHF[1] = lock[0].A[1] - lock[0].index[1] - PHF[1];
	ULHF[2] = lock[0].A[2] - lock[0].index[2] - PHF[2];
	ULHF[3] = lock[0].A[3] - lock[0].index[3] - PHF[3];
	for (int i = 0; i < 4; i++) {
		if (ULHF[i] >= 10) {
			ULHF[i] = (ULHF[i] - 10);
		}
		if (ULHF[i] < 0)
			ULHF[i] = ULHF[i] + 10;
		cout << ULHF[i] << endl;
	}
	for (int i = 0; i < 10000; i++) {
		UHF[i][0] = i / 1000;
		UHF[i][1] = i / 100 - UHF[i][0] * 10;
		UHF[i][2] = i / 10 - UHF[i][0] * 100 - UHF[i][1] * 10;
		UHF[i][3] = i - UHF[i][0] * 1000 - UHF[i][1] * 100 - UHF[i][2] * 10;
	}
	
	for (int i = 0; i < 10000; i++) {

		for (int j = 0; j < 100; j++) {
			hfun->HashCN(lock[j].index, UHF[i]);
			safetemp = hfun->getCN();
			if (i == 8244) {
				cout << safetemp[0] << safetemp[1] << safetemp[2] << safetemp[3] << "chk-------------" << endl;
			}
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false) {
				break;
			}
			hfun->HashCN(HN0[j], UHF[i]);
			safetemp = hfun->getCN();
			if (i == 8244) {
				cout << HN0[j][0] << HN0[j][1] << HN0[j][2] << HN0[j][3] << endl;
				cout << safetemp[0] << safetemp[1] << safetemp[2] << safetemp[3] << "chk-------------" << endl;
			}
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false) {
				break;
			}
			hfun->HashCN(HN1[j], UHF[i]);
			safetemp = hfun->getCN();
			if (i == 8244) {
				cout << safetemp[0] << safetemp[1] << safetemp[2] << safetemp[3] << "chk-------------" << endl;
			}
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false) {
				break;
			}
			hfun->HashCN(HN2[j], UHF[i]);
			safetemp = hfun->getCN();
			if (i == 8244) {
				cout << safetemp[0] << safetemp[1] << safetemp[2] << safetemp[3] << "chk-------------" << endl;
			}
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false) {
				break;
			}
			hfun->HashCN(HN3[j], UHF[i]);
			safetemp = hfun->getCN();
			if (i == 8244) {
				cout << safetemp[0] << safetemp[1] << safetemp[2] << safetemp[3] << "chk-------------" << endl;
			}
			sf->chkCN(safetemp);
			safeCN = sf->reCNSafe();
			if (safeCN == false) {
				break;
			}
			if (j = 99) {
				chkcounter++;
				cout << UHF[i][0] << UHF[i][1] << UHF[i][2] << UHF[i][3] << "here!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
				cout << chkcounter << endl;
			}
		}

		//cout << UHF[i][0] << UHF[i][1] << UHF[i][2] << UHF[i][3] <<endl;
	}
}
