/**
  Zadani su prirodan broj $n$ i permutacija brojeva 0, 1, ..., N = 2^n - 1.
  Interval (podsegment) permutacije je "dobar" ako postoji swap (na cijeloj permutaciji, ne samo na intervalu)
  nakon kojega je njegov XOR jednak N. (postavi kao igru)
  Koliko ima dobrih podsegmenata?

  RJESENJE:
  Za n = 1 je rjesenje 2 za obje permutacije. Promatrajmo n >= 2.
  Nazovimo ne-dobre (neprazne) intervale losima. Karakterizirat cemo lose intervale.

  T: Interval je los ako i samo ako se skup elemenata od kojih se sastoji moze podijeliti u parno mnogo
  disjunktnih parova {x, N XOR x}.
 
  P:
  Ako je interval duljine 1, uvijek je dobar. (Ako je N, swapamo nesto izvan, inace swapamo s N.)
  Interval koji se sastoji od cijele permutacije je los jer mu je XOR svih elemenata 0 
  i ne mijenja se nijednim swapom. On ujedno i zadovoljava karakterizaciju jer 4 | N + 1.

  Pretpostavimo da je inverval I s 2 <= |I| <= N los. Neka je XOR svih elemenata od I jednak A.
  Tada ne postoje x iz I i y izvan I takvi da je A XOR x XOR y = N. (Lijeva strana je XOR intervala I
  nakon swapanja x i y.)
  Ekvivalentno, ne postoje x iz I i y izvan I takvi da je x XOR y = A XOR N = !A.
  To implicira da je, za svaki x u I, y = x XOR !A unutar I.
  Ne moze vrijediti !A = 0, jer je A = N, pa bi interval bi bio dobar. (Swapamo neka dva elementa iz I.)
  Zato, posto je (x XOR !A) XOR !A = x za svaki x, i x XOR !A nije isto sto i x ni za jedan x, 
  skup elemenata u intervalu I mozemo podijeliti u parove {x, x XOR !A}. Neka je |I| = 2M.
  XOR svakog para je jednak !A, pa je XOR cijelog intervala (A) jednak !A XOR-anom samim sa sobom M puta.
  Ako je M neparan, prethodna tvrdnja daje A = (!A XOR !A) XOR ... XOR (!A XOR !A) XOR !A = !A , sto ne moze vrijediti.
  Zato je M paran i A = (!A XOR !A) XOR ... XOR (!A XOR !A) = 0, tj. !A = N, sto implicira pocetnu karakterizaciju.

  Za drugi smjer, primijetimo da je XOR karakteriziranog intervala jednak 0, pa bi swap
  koji bi ucinio da mu je XOR jednak N trebao biti oblika (x iz I <--> x XOR N izvan I),
  sto nije moguce jer je x XOR N unutar I po definiciji.
  

  Sada moramo prebrojiti lose intervale. 
  
  Primijetimo da skup {0, 1, ..., (N-1)/2} sadrzi po tocno jedan element iz svakog para {x, N XOR x}.

  Odaberimo neki prirodan broj k i prirodne brojeve a_0, ..., a_{(N-1)/2}.
  U pocetnoj permutaciji zamijenimo svaki par {x, N XOR x}, gdje je 0 <= x <= (N-1)/2, 
  parom {a_x, k XOR a_x}.

  T: Los interval u pocetnoj permutaciji postaje interval XOR-a 0 u novom nizu.
  P: XOR svakog para {a_x, k XOR a_x} je k, a los interval sadrzi parno mnogo parova.
  
  T: Interval XOR-a 0 u novom nizu koji u je pocetnoj permutaciji bio dobar implicira relaciju oblika
              a_{s_1} XOR ... XOR a_{s_t} = 0 ili k
    za neki t i neke razlicite 0 <= s_i <= (N-1)/2, 1 <= i <= t.
  P: 
  Pretpostavimo da je XOR intervala I jednak 0 u novom nizu. Interval se u originalnoj permutaciji
  ne moze sastojati samo od neparno  mnogo parova {x, N XOR x} jer bi mu XOR u novom nizu bio k > 0. 
  Zato postoji t >= 1 parova {x, N XOR x} s kojima I ima jednoclan presjek. Neka su ti x-evi 
  (biramo 0 <= x <= (N-1)/2)  s_1, ..., s_t. 
  Direktnim uvrstavanjem u novi niz dobiva se prethodna relacija.

  
  Kada bismo bili sigurni da nijedna relacija opisanog oblika ne vrijedi, dovoljno bi bilo prebrojati
  intervale XOR-a 0 u novom nizu. Taj problem mozemo rijesiti matematicki:
  Neka je p[i] XOR prvih i elemenata niza, i definirajmo p[0] = 0. Interval [i, j> u novom nizu 
  ima XOR 0 ako i samo ako je p[i] XOR p[j] = 0, tj. p[i] = p[j].
  Svaki par jednakih p[i]-eva za i = 0, ..., N+1 daje jedan interval XOR-a 0, pa je broj trazenih 
  intervala jednak 
            \sum_{m nenegativan cijeli}{ \binom{broj p[i]-jeva jednakih m}{2} }.
  Brojeve istih p[i]-jeva mozemo izracunati koristeci std::map (slozenost O(N log N)),
  odnosno standardnim sortiranjem i kompresijom u istoj slozenosti. 
  Idealno, mozemo koristiti std::unordered_map (ocekivana slozenost O(N)).


  Naravno, ne mozemo lako (koliko je poznato autoru zadatka) osigurati da nijedna relacija tog oblika ne vrijedi.
  Medutim, ako vise puta slucajno odaberemo brojeve a_0, a_1, ..., a_{(N-1)/2} iz npr. intervala pozitivnih
  vrijednosti tipa int u c++, nijedna relacija vrlo vjerojatno nece vrijediti bas svaki put. Naravno, moguce je
  da svaki put vrijede neke razlicite relacije, ali to nas uopce ne mora brinuti.

  Odaberimo r nizova a_x, te napravimo novi niz iz pocetne permutacije za svaki od r nizova a_x. 
  Neka je p[i][z] XOR prvih i elemenata u z-tom nizu, 0 <= z <= r-1. Analogno kao i prije, dobivamo da moramo
  brojati iste p[i], ovaj put po svim komponentama. To opet mozemo postici u O(N log N * r) sa std::map
  ili ocekivano u O(N * r) sa std::unordered_map.

  U sluzbenom rjesenju uzeli smo r = 5 i random a-ove tipa int. 
  Takoder, svaki put smo random odabrali k tipa int. Potencijalno dobra ideja je odabrati k
  koji ima najveci bit veci od svih a-ova kako bi prepolovili broj relacija koje mogu smetati.
**/

#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <map>
#include <unistd.h>

#define TRACE(x) cerr << #x << " " << x << endl

using namespace std;
const int MaxN = (1 << 20) + 5;
const int numOfRandSequences = 5;
int n, N;
int perm[MaxN];

const int hashMod = 31;
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


array <int, numOfRandSequences> k;
vector <array <int, numOfRandSequences>> a;
vector <array <int, numOfRandSequences>> replacementBigLabel;

vector <array <int, numOfRandSequences>> prefiXOR;
map <array <int, numOfRandSequences>, int> Map; 
//unordered_map <array <int, numOfRandSequences>, int, HASH> Map; 

inline long long binom2(int x){
  return (long long) x * (x - 1) / 2;
}

array <int, numOfRandSequences> xorOfArrays(array <int, numOfRandSequences>& A, array <int, numOfRandSequences>& B){
  array <int, numOfRandSequences> ret;
  for (int i = 0; i < numOfRandSequences; i++){ 
    ret[i] = (A[i] ^ B[i]);
  }
  return ret;
}

long long solution(){
  if (n == 1)
    return 2;

  for (int z = 0; z < numOfRandSequences; z++){
    k[z] = rand();
  }
  
  for (int i = 0; i <= (N - 1) / 2; i++){
    a.emplace_back();
    for (int z = 0; z < numOfRandSequences; z++){
      a[i][z] = (rand());
    }
  }

  for (int i = 0; i <= N; i++){
    int x = perm[i];
    replacementBigLabel.emplace_back();
    for (int z = 0; z < numOfRandSequences; z++)
      if (x <= (N - 1)/2){
        replacementBigLabel[i][z] = (a[x][z]);
      }
      else{
        replacementBigLabel[i][z] = ((k[z]) ^ (a[x ^ N][z]));
      }
  }

  prefiXOR.emplace_back();
  for (int z = 0; z < numOfRandSequences; z++){
    prefiXOR[0][z] = (0);
  }
  
  for (int i = 0; i <= N; i++){
    prefiXOR.emplace_back(xorOfArrays(prefiXOR[i], replacementBigLabel[i]));  
  }

  for (auto& xors: prefiXOR){
    Map[xors] += 1;
  }
  
  long long badIntervals = 0;
  for (auto& xors: prefiXOR){
    if (Map[xors] > 0){
      badIntervals += binom2(Map[xors]);
      Map[xors] = 0;
    }
  }

	TRACE(badIntervals);
  return binom2(N + 2) - badIntervals;
}

void load(){
  scanf("%d", &n);
  N = (1 << n) - 1;
  for (int i = 0; i <= N; i++)
    scanf("%d", perm + i);
}

int main(){
  srand((int)time(0) * getpid());
  load();
  cout<<solution()<<endl;
  return 0;
}
