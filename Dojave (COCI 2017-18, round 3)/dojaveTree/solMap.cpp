#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

const int MaxN = (1 << 20) + 5;
const int numOfRandSequences = 4;
const size_t hashMod = 37;

struct OutEdge {
	int vertex; 
	int label;
	OutEdge(int vertex, int label) : vertex(vertex), label(label) {}
};

struct HASH{
  size_t operator() (const array<int, numOfRandSequences>& arr) const{
    size_t rollingHash = 1;
		for (auto &x: arr){
			rollingHash *= hashMod;
			rollingHash += (size_t)x;
		}
		return rollingHash;
  }
};

int N, n;
vector <OutEdge> adj[MaxN];
bool been[MaxN];

array <int, numOfRandSequences> k;
vector <array <int, numOfRandSequences>> a;
vector <array <int, numOfRandSequences>> replacementBigLabel;

vector <array <int, numOfRandSequences>> rootedXOR;
//unordered_map <array <int, numOfRandSequences>, int, HASH> Map;
map <array <int, numOfRandSequences>, int> Map;


inline long long binom2(int x){
  return (long long) x * (x - 1) / 2;
}

array <int, numOfRandSequences> xorOfArrays(const array <int, numOfRandSequences> A, const array <int, numOfRandSequences> B){
  array <int, numOfRandSequences> ret;
  for (int i = 0; i < numOfRandSequences; i++){
    ret[i] = (A[i] ^ B[i]);
  }
  return ret;
}

void dfs(const int node, const array <int, numOfRandSequences> prevRootedXOR){
	been[node] = true;
	rootedXOR[node] = prevRootedXOR;

	for (auto &edge: adj[node]){
		if (!been[edge.vertex]){
			dfs(edge.vertex, xorOfArrays(prevRootedXOR, replacementBigLabel[edge.label]));
		}
	}
}

long long solution(){
  if (n == 1)
    return 2;

	int root = 1;

  for (int z = 0; z < numOfRandSequences; z++){
    k[z] = rand();
  }

  for (int i = 0; i <= (N - 1) / 2; i++){
    a.emplace_back();
    for (int z = 0; z < numOfRandSequences; z++){
      a[i][z] = (rand());
    }
  }

  for (int label = 0; label <= N; label++){
		replacementBigLabel.emplace_back();
    for (int z = 0; z < numOfRandSequences; z++)
      if (label <= (N - 1)/2){
        replacementBigLabel[label][z] = (a[label][z]);
      }
      else{
        replacementBigLabel[label][z] = ((k[z]) ^ (a[label ^ N][z]));
      }
  }


	rootedXOR.resize(N + 2); // N + 2 vertices
  
	for (int z = 0; z < numOfRandSequences; z++){
    rootedXOR[root][z] = (0);
  }

	dfs(root, rootedXOR[root]);

  for (auto& xors: rootedXOR){
    Map[xors] += 1;
  }

  long long badPaths = 0;
  for (auto& xors: rootedXOR){
    if (Map[xors] > 0){
      badPaths += binom2(Map[xors]);
      Map[xors] = 0;
    }
	}

	// binom2(N + 2) is the number of paths (including one-edge paths)
  return binom2(N + 2) - badPaths;
}


void load(){
	scanf("%d", &n);
	N = (1 << n) - 1;
	for (int i = 0; i < N + 1; i++){ // N + 1 edges
		int ta, tb, label;
		scanf("%d %d %d", &ta, &tb, &label);
		ta--; tb--;
		adj[ta].emplace_back(OutEdge{tb, label});
		adj[tb].emplace_back(OutEdge{ta, label});
	}
}

int main(){
	load();
	cout<<solution()<<endl;
	return 0;
}


