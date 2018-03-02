#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << "  " << x << endl
#define eb emplace_back
#define _ << " " <<
using namespace std;

const int MaxN = (1 << 15) + 5;
const int Mod_e97 = 1e9 + 7;

struct OutEdge {
	int vertex;
	int label;
	OutEdge(int vertex, int label) : vertex(vertex), label(label) {}
};

int N, n;
vector <OutEdge> adj[MaxN];
int rootedXOR[MaxN];
int depth[MaxN];
bool been[MaxN];
int parent[MaxN];
int anc[MaxN][21];
pair <int, int> vertices[MaxN]; //vertices of edge

void dfsDepth(int node, int curDist){
	been[node] = 1;
	depth[node] = curDist;
	for (auto edge: adj[node]){
		if (!been[edge.vertex]){
			parent[edge.vertex] = node;
			dfsDepth(edge.vertex, curDist + 1);
		}
	}
}

void prepLCA(int rootNode){
	memset(been, 0, sizeof been);
	parent[rootNode] = rootNode;
	dfsDepth(rootNode, 0);

	REP(i, N + 2)
		for (int k = 0; (1 << k) < (N + 2); k++)
			anc[i][k] = -1;

	REP(i, N + 2)
		anc[i][0] = parent[i];

	for (int k = 1; (1 << k) < (N + 2); k++)
		REP(i, N + 2)
			if (anc[i][k] == -1)
				anc[i][k] = anc[ anc[i][k - 1] ][k - 1];
}

int queryLCA(int x, int y){
	if (depth[x] < depth[y]) swap(x, y);

	int logL;
	for (logL = 1; (1 << logL) <= depth[x]; logL++);
	logL--;

	for (int i = logL; i >= 0; i--)
		if (depth[x] - (1 << i) >= depth[y])
			x = anc[x][i];

	if (x == y) return x;

	for (int i = logL; i >= 0; i--)
		if (anc[x][i] != -1 && (anc[x][i] != anc[y][i]))
			{ x = anc[x][i], y = anc[y][i]; }

	return parent[x];
}

void dfsXOR(int node, int currentXOR){
	been[node] = true;
	rootedXOR[node] = currentXOR;
	for (auto edge: adj[node]){
		if (!been[edge.vertex])
			dfsXOR(edge.vertex, currentXOR ^ edge.label);
	}
}

bool isOnPath(int node, int x, int y){
	int lcaX = queryLCA(node, x);
	int lcaY = queryLCA(node, y);
	int lcaXY = queryLCA(x, y);
	
	if (lcaX == lcaXY){
		if (lcaY == node)
			return true;
		else
			return false;
	}
	
	if (lcaY == lcaXY){
		if (lcaX == node)
			return true;
		else
			return false;
	}

	return false;
}

bool isLabelOnPath(int label, int x, int y){
	bool prvi = isOnPath(vertices[label].first, x, y);
	bool drugi = isOnPath(vertices[label].second, x, y);
	return prvi && drugi;
}

inline long long binom2(int x){
	return (long long) x * (x - 1) / 2;
}

long long solution(){
	if (n == 1)
		return 2;

	memset(been, 0, sizeof been);
	dfsXOR(0, 0);
	prepLCA(0);

	long long badPaths = 0;

	REP(x, N + 2){
		FOR(y, x + 1, N + 2){
			int target = rootedXOR[x] ^ rootedXOR[y] ^ N;
			if (target == 0) continue;

			bool ok = false;
			
			REP(label, N + 1){
				if (isLabelOnPath(label, x, y) && !isLabelOnPath(target ^ label, x, y)){
					ok = true;
					break;
				}
			}
			if (!ok) badPaths++;
		}
	}

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
		vertices[label] = {ta, tb};
	}
}


int main(){
	load();
	cout<<solution()<<endl;
	return 0;
}



