#include <cstdio>
#include <cmath>
#include <cstring>
const int maxn = 10000000;
const int maxp = 700000;
struct Factor{ // factor as p^num
  int p, num;
};
struct DeComposer {
  bool vis[maxn+5];
  int pn, prime[maxp];
  void sieve() {
    int m = (int)sqrt(maxn+0.5);
    memset(vis,0,sizeof(vis));
    for(int i=2;i<=m;++i)if(!vis[i])
      for(int j=i*i;j<=maxn;j+=i)vis[j]=1;
  }
  void gen_primes() {
    sieve();
    pn = 0;
    for (int i = 2; i <= maxn; ++ i) {
      if (!vis[i]) prime[pn++] = i;
    }
  }
  int fcn;
  Factor fc[64]; // x = p1^a1 * p2^a2 * ...
  int fn, factor[maxp]; // all y satisify y|x
  void decompose2(int x,int d){
    if(d==fcn){
      factor[fn++] = x;
    } else {
      for(int i = 0; i <= fc[d].num; ++ i) {
        decompose2(x, d+1);
        x *= fc[d].p;
      }
    }
  }
  void decompose1(int x) {
    fcn = 0;
    for(int i = 0; i < pn && prime[i] * prime[i] <= x; ++ i) if (x % prime[i] == 0) {
      fc[fcn].p = prime[i];
      fc[fcn].num = 0;
      while(x % prime[i] == 0) {
        fc[fcn].num ++;
        x /= prime[i];
      }
      fcn ++;
    }
    if (x > 1) {
      fc[fcn].p = x;
      fc[fcn].num = 1;
      fcn ++;
    }
  }
  void decompose(int x){
    decompose1(x);
    fn = 0;
    decompose2(1,0);
  }
} dc_solver;
int main() {
}

