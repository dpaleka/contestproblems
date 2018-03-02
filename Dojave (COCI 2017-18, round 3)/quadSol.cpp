#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

const int LogMaxN = 20;
const int MaxN = (1 << LogMaxN) + 5;
const int Mod_e97 = 1e9 + 7;

inline long long binom2(int x){
  return (long long) x * (x - 1) / 2;
}

int n, N;
int perm[MaxN];
int invPerm[MaxN];

int ceilLogTwo[MaxN];
int mins[LogMaxN][MaxN];
int maxs[LogMaxN][MaxN];

void precomputeCeilLogTwo(){
	ceilLogTwo[1] = 0;
	for (int i = 2; i <= N + 1; i++){
		ceilLogTwo[i] = ceilLogTwo[i / 2] + 1;
	}
}

void precomputeConst(){
	for (int i = 0; i <= N; i++){
		mins[0][i] = maxs[0][i] = invPerm[N - perm[i]];
	}

	for (int pot = 0; pot <= n; pot++){
    for (int i = 0; i <= N; i++) {
      mins[pot + 1][i] = min(
        mins[pot][i],
        i + (1<<pot) <= N ? mins[pot][i + (1<<pot)] : N + 1
      );
			maxs[pot + 1][i] = max(
				maxs[pot][i],
				i + (1<<pot) <= N ? maxs[pot][i + (1 << pot)] : -1
			);
    }
  }
}

int maxPair(int left, int right){ // [left, right>
	int greatestPowTwo = ceilLogTwo[right - left];
	return max(
			maxs[greatestPowTwo][left],
			maxs[greatestPowTwo][right - (1 << greatestPowTwo)]
	);
}

int minPair(int left, int right){ // [left, right>
	int greatestPowTwo = ceilLogTwo[right - left];
	return min(
			mins[greatestPowTwo][left],
			mins[greatestPowTwo][right - (1 << greatestPowTwo)]
	);
}

long long solution(){
	long long badIntervals = 0;

	for (int L = 0; L <= N; L++){
		int R = L;
		while (R <= N){
			if (minPair(L, R + 1) < L)
				break;

			int wantedR = maxPair(L, R + 1);
	
			// evaluation
			if ((R - L + 1) % 4 == 0 && wantedR == R){
				badIntervals++;
//				TRACE(perm[L]); TRACE(perm[R]);
			}

			// continuation
			R = max(wantedR, R + 1);
		}
	}

//	TRACE(badIntervals);
	return binom2(N + 2) - badIntervals;
}

void load(){
	scanf("%d", &n);
	N = (1 << n) - 1;
	for (int i = 0; i <= N; i++){
		scanf("%d", perm + i);
		invPerm[perm[i]] = i;
	}
}

int main(){
	load();
	if (n == 1){
		cout << 2 << endl;
		return 0;
	}
	precomputeConst();
	precomputeCeilLogTwo();
	cout << solution() << endl;
	return 0;
}


