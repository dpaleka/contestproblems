#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

const int MaxN = (1 << 20) + 5;
const int nLO = 1;
const int nHI = 20;

int n, N;
int perm[MaxN];
int appear[MaxN];

int main(){
	scanf("%d", &n);
	
	assert(nLO <= n && n <= nHI);
	
	N = (1 << n);
	REP(i, N){
		scanf("%d", perm + i);
		assert(0 <= perm[i] && perm[i] <= N);
		appear[perm[i]]++;
	}

	REP(i, N)
		assert(appear[i] == 1);
		
	puts("OK!");
	return 0;
}


