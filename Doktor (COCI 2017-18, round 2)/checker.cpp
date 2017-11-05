#include <cassert>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int MaxN = 500500;

typedef long long llint;

void zavrsi(string bodovi, string poruka);

int N;
int perm[MaxN];
int taken[MaxN];

int sluzbAns[2], natjAns[2];

void input_input(ifstream &finput) {		
	if (!(finput >> N))
		zavrsi("0", "Fatal testcase error!");

	for (int i = 1; i <= N; i++) 
		if (!(finput >> perm[i]))
			zavrsi("0", "Fatal testcase error!");

	for (int i = 1; i <= N; i++)
		if (perm[i] < 1 || perm[i] > N)
			zavrsi("0", "Invalid testcase!");

	for (int i = 1; i <= N; i++)
		taken[perm[i]]++;

	for (int i = 1; i <= N; i++)
		if (taken[i] != 1)
			zavrsi("0", "Invalid testcase!");
}

void input_sluzb(ifstream &fsluzb) {
	for (int z = 0; z < 2; z++)
		if (!(fsluzb >> sluzbAns[z])) zavrsi("0", "Fatal official solution error!");
}


void rotateSegment(int left, int right){ // [left, right]
	for (int z = 0; z <= (right - left) / 2; z++)
		swap(perm[left + z], perm[right - z]);
}

int countFixedPoints(){
	int ret = 0;
	for (int i = 1; i <= N; i++)
		ret += (perm[i] == i);
	return ret;
}

void input_natj(ifstream &fnatj)
{
	for (int z = 0; z < 2; z++)
		if (!(fnatj >> natjAns[z]))
			zavrsi("0", "Wrong output format!");

	if (natjAns[0] < 1 || natjAns[0] > N || natjAns[1] < 1 || natjAns[0] > N)
		zavrsi("0", "A card with some of the given numbers doesn't exist!");

	int natjLeft = -1, natjRight = -1;
	for (int i = 1; i <= N; i++){
		if (perm[i] == natjAns[0])
			natjLeft = i;
		if (perm[i] == natjAns[1])
			natjRight = i;
	}

	if (natjLeft == -1 || natjRight == -1 || natjRight < natjLeft)
		zavrsi("0", "Invalid description of subarray!");

	int sluzbLeft = -1, sluzbRight = -1;	
	for (int i = 1; i <= N; i++){
		if (perm[i] == sluzbAns[0])
			sluzbLeft = i;
		if (perm[i] == sluzbAns[1])
			sluzbRight = i;
	}

	rotateSegment(sluzbLeft, sluzbRight);
	int sluzbSol = countFixedPoints();
	rotateSegment(sluzbLeft, sluzbRight);

	rotateSegment(natjLeft, natjRight);
	int natjSol = countFixedPoints();
	rotateSegment(natjLeft, natjRight);

	if (sluzbSol != natjSol)
		zavrsi("0", "The number of fixed points is not maximal!");

	string crap;
	if (fnatj >> crap)
		zavrsi("0", "Too much output!");	
	zavrsi("1", "Correct!");
}

void zavrsi(string bodovi, string poruka) {
	cout << bodovi << '\n';
	cout << poruka << '\n';
  	exit(0);
}

int main(int argc, char *argv[])
{
	assert(argc == 4);

	ifstream finput(argv[1]);
	ifstream fsluzb(argv[2]);
	ifstream fnatj(argv[3]);

	assert(!finput.fail() && !fsluzb.fail() && !fnatj.fail());

	input_input(finput);
	input_sluzb(fsluzb);
	input_natj(fnatj);
	
	return 0;
}
