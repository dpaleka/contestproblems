#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

//const int MaxN = 200100;
//const int Mod_e97 = 1e9 + 7;

int n, N;
vector <int> labels;

void load(){
	cin>>n;
	N = (1 << n) - 1;
	REP(i, N + 1)
		labels.eb(i);
}

void output(){
	cout<<n<<endl;
	REP(i, N + 1){
		cout << i + 1 << " " << i + 2 << " " << labels[i] << endl;
	}
}

int main(){
	ios::sync_with_stdio(false);
	load();	

	std::random_device rd;
  std::mt19937 g(rd());

	shuffle(labels.begin(), labels.end(), g);
	
	output();
	return 0;
}


