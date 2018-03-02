#include <cassert>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

typedef long long llint;
typedef unsigned long long ullint;

const int MaxT = 255000;
const llint TRESHOLD = 1e15;

void zavrsi (string bodovi, string poruka);
int digitSum (ullint x);
ullint seqMember (llint N);

int c, d, B, T;

llint sluzbAns[MaxT], natjAns[MaxT];

void input_input(ifstream &finput) {		
	if (!(finput >> c) || !(finput >> d) || !(finput >> B) || !(finput >> T))
		zavrsi("0", "Fatal testcase error!");
}

void input_sluzb(ifstream &fsluzb) {
  for (int i = 0; i < T; i++){
		if (!(fsluzb >> sluzbAns[i])) zavrsi("0", "Fatal official solution error!");
    if (sluzbAns[i] < 1 || sluzbAns[i] > TRESHOLD) zavrsi("0", "Official solution error: number outside limits!");
  }

  int target = digitSum(seqMember(sluzbAns[0]));

  for (int i = 1; i < T; i++)
    if (digitSum(seqMember(sluzbAns[i])) != target){
      cerr << sluzbAns[i] << " " << digitSum(seqMember(sluzbAns[i])) << " " << target << endl; 
      zavrsi("0", "Official solution error: wrong solution!");
    }
}

int digitSum(ullint x) {
    int ret = 0;
    while (x > 0){
        ret += x % B;
        x /= B;
    }
    return ret;
}

ullint seqMember(llint N) {
    return ((ullint)c) * N + d;
}

void input_natj(ifstream &fnatj) {
	set<long long> izlazni_set;

  for (int i = 0; i < T; i++){
		if (!(fnatj >> natjAns[i])) zavrsi("0", "Wrong output format!");
    if (natjAns[i] < 1 || natjAns[i] > TRESHOLD) zavrsi("0", "Solution error: number outside limits!");
  }

  int target = digitSum(seqMember(natjAns[0]));

  for (int i = 1; i < T; i++)
    if (digitSum(seqMember(natjAns[i])) != target) zavrsi("0", "Wrong solution!");

  for (int i = 0; i < T; i++){
    izlazni_set.insert(natjAns[i]);
  }

  if ((int)izlazni_set.size() != T)
    zavrsi("0", "Numbers are not unique!");

	string trash;
	if (fnatj >> trash)
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
