#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

//const int MaxN = 200100;
//const int Mod_e97 = 1e9 + 7;

random_device rd;
std::mt19937 g(rd());

int groupSizeHalf;
int n, N;
vector <int> labels;
vector <vector <int>> groups;

void load(){
	cin>>n>>groupSizeHalf;
	N = (1 << n) - 1;
}

void makeGroups(){
	int cnt = 0;
	REP(i, (N + 1)/2){
		if (cnt == 0)
			groups.eb();
		groups[groups.size() - 1].eb(i);
		groups[groups.size() - 1].eb(N ^ i);
		cnt++;
		//TRACE(cnt);
		if (cnt == groupSizeHalf)
			cnt = 0;
	}
}

void permuteGroups(){
	for (auto &group: groups){		
		shuffle(group.begin(), group.end(), g);
	}
}

void contacenateGroups(){
	for (auto &group: groups){
		for (auto element: group)
			labels.eb(element);
	}
}

void output(){
	cout<<n<<endl;
	REP(i, N + 1){
		cout << labels[i] << " \n"[i == N];
	}
}

int main(){
	ios::sync_with_stdio(false);
	load();	
	makeGroups();
	permuteGroups();	
	contacenateGroups();
	output();
	return 0;
}


