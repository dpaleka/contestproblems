#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
#define __ << " " <<
typedef long long ll;
typedef std::pair<int, int> P;
#define X first
#define Y second
#define double long double
using namespace std;

const int MaxS = 50100;

vector <int> bucket[MaxS];

int c, d, B, T;

inline int digitSum(ll x){
  int ret = 0;
  while (x > 0){
    ret += x % B;
    x /= B;
  }
  return ret;
}

inline int toBucket(int sumOfDigits){
  return sumOfDigits;
}

inline ll seqMember(int N){
  return ((ll)c) * N + d;
}

void output(vector <int> &V, int whatBucket, int whichStep){
  printf("DA\n");
  for (auto x: V)
    printf("%lld ", x);
  //    printf("\n%d %d\n", whatBucket, whichStep);
}

void solve(){
  for (int N = 1; N <= 1e9; N++){
    ll num = seqMember(N);
    int sumOfDigits = digitSum(num);
    int compressedDigitSum = toBucket(sumOfDigits);

    bucket[compressedDigitSum].push_back(N);
    if ((int)bucket[compressedDigitSum].size() >= T){
      output(bucket[compressedDigitSum], compressedDigitSum, N);
      break;
    }
  }
}

void load(){
  scanf("%d%d%d%d", &c, &d, &B, &T);
}

int main(){
  load();	
  solve();
  return 0;
}


