#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int offset = 1 << 21;

struct node {
	int cnt[4];
	bool lazy;
};

int N;
int a[offset];
int last[offset];
set <int> S;
node t[2 * offset];

void load() {
	int n;
	scanf("%d", &n);
	N = 1 << n;
	for (int i = 1; i <= N; i++)
		scanf("%d", a + i);
}

node merge(node l, node r) {
	node res;
	for (int i = 0; i < 4; i++)
		res.cnt[i] = l.cnt[i] + r.cnt[i];
	res.lazy = false;
	return res;
}

void prop(int x) {
	if (!t[x].lazy)
		return;
	memset(t[x].cnt, 0, sizeof t[x].cnt);
	if (x < offset)
		t[2 * x].lazy = t[2 * x + 1].lazy = true;
	t[x].lazy = false;
}

void update(int x, int lo, int hi, int from, int to) {
	prop(x);
	if (lo >= to || hi <= from)
		return;
	if (lo >= from && hi <= to) {
		memset(t[x].cnt, 0, sizeof t[x].cnt);
		if (x < offset)
			t[2 * x].lazy = t[2 * x + 1].lazy = true;
		return;
	}
	int mid = (lo + hi) / 2;
	update(2 * x, lo, mid, from, to);
	update(2 * x + 1, mid, hi, from, to);
	t[x] = merge(t[2 * x], t[2 * x + 1]);
}

void update(int from, int to) {
	update(1, 0, offset, from, to);
}

node query(int x, int lo, int hi, int from, int to) {
	prop(x);
	if (lo >= to || hi <= from)
		return {0, 0, 0, 0, false};
	if (lo >= from && hi <= to)
		return t[x];
	int mid = (lo + hi) / 2;
	return merge(query(2 * x, lo, mid, from, to), query(2 * x + 1, mid, hi, from, to));
}

int query(int from, int to) {
	return query(1, 0, offset, from, to).cnt[to % 4];
}

ll solve() {
	if (N == 2)
		return 2;
		
	for (int i = 1; i <= N; i++)
		if (a[i] & 1)
			a[i] ^= N - 1;
	
	for (int i = 0; i <= N; i++)
		t[i + offset].cnt[i % 4]++;
	
	for (int i = offset - 1; i >= 0; i--)
		t[i] = merge(t[2 * i], t[2 * i + 1]);
		
	S.insert(0);
	ll sol = 0;
	for (int i = 1; i <= N; i++) {
		if (!last[a[i]])
			S.insert(i);
		else {
			S.erase(last[a[i]]);
			update(last[a[i]], i);
		}
		sol += query(*S.rbegin(), i);
		last[a[i]] = i;
	}
	
	return (ll)N * (N + 1) / 2 - sol;
}

int main() {
	load();
	printf("%lld\n", solve());
	return 0;
}
