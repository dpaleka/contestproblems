#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

const int MaxN = 1000100;

int N;
vector <int> nums;

void create(){
	REP(i, N)
		nums.eb(N - i);
	
	random_shuffle(nums.begin(), nums.end()); 

	printf("%d\n", N);

	for (auto x: nums)
		printf("%d ", x);
}

void load(){
	cin>>N;
}

int main(){
	srand(time(NULL));
	load();
	create();
	return 0;
}


