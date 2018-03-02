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

const int MaxS = 500;

int bucket[MaxS];

int c, d, B, T;

int digitSum(ll x){
    int ret = 0;
    while (x > 0){
        ret += x % B;
        x /= B;
    }
    return ret;
}

int toBucket(int sumOfDigits){
    return sumOfDigits / (B - 1);
}

ll seqMember(int N){
    return ((ll)c) * N * (B - 1) + d;
}

void output(int targetSum){
  printf("DA\n");
  
  for (int N = 1; N <= 1e9; N++){
    ll num = seqMember(N);
    int sumOfDigits = digitSum(num);
    if (sumOfDigits == targetSum){
      printf("%lld ", (ll)N * (B - 1) );
      T--;
      if (T == 0) return;
    }
  }
}

void solve(){
    for (int N = 1; N <= 1e9; N++){
        ll num = seqMember(N);
        int sumOfDigits = digitSum(num);
        int compressedDigitSum = toBucket(sumOfDigits);
        
        bucket[compressedDigitSum]++;
        if (bucket[compressedDigitSum] >= T){
            output(sumOfDigits);
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


