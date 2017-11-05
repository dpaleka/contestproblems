#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

const int MaxN = 500100;

//everything is 1-indexed

int N;
int perm[MaxN];

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

void solve(){
	int targetMax = -1, targetLeft = -1, targetRight = -1;
	
	for (int left = 1; left <= N; left++)
		for (int right = left; right <= N; right++){
			rotateSegment(left, right);
		
			int res = countFixedPoints();
	
			if (targetMax < res){
				targetMax = res;
				targetLeft = left;
				targetRight = right;
			}

			rotateSegment(left, right);
		}

	printf("%d %d\n", perm[targetLeft], perm[targetRight]);
}

void load(){
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", perm + i);
}

int main(){
	load();
	solve();
	return 0;
}


