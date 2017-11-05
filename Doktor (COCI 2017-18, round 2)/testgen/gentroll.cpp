#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

const int MaxN = 1000100;

int N;

void create(){
	printf("%d \n", N);
	REP(i, N){
		printf("%d ", i + 1);
	}
}

void load(){
	cin>>N;
}

int main(){
	load();
	create();
	return 0;
}


