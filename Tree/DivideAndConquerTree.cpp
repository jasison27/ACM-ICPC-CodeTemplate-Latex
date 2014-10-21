//hdu 4812 D Tree
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#pragma comment(linker,"/STACK:102400000,102400000")
using namespace std;
const int maxn = 1e5 + 10;
const int md = 1e6 +3;
int N,K;
vector<int > edge[maxn];
void add_edge(int from,int to) {
  edge[from].push_back(to);
}
void init() {
  for(int i = 1;i <= N;i ++) edge[i].clear();
}
int vi[maxn];
int vis[maxn];
int root;
int mi;
int son[maxn];
int hash[md + 10];
int vers[md + 10];
int verc;
pair<int , int > ans;
int fastpow(int x,int y) {
  int ret = 1 ,mul = x;
  while(y) {
    if(y & 1 ) ret = 1LL * mul * ret % md;
    mul = 1LL * mul* mul % md;
    y >>= 1;
  }
  return ret;
}
int comm[md + 10];
void inv1() {
  for(int i = 0;i < md;i ++) {
    comm[i] = fastpow(i,md - 2);
  }
}
int inv(int t) {
  return comm[t];
}
void getroot(int t,int sz) {
  vis[t] = true;
  son[t] = 1;
  int mx = 0;
  for(int i = 0;i < edge[t].size();i ++) {
    int nxt = edge[t][i];
    if(!vis[nxt]) {
      getroot(nxt,sz);
      son[t] += son[nxt];
      mx = max(mx,son[nxt]);
    }
  }
  mx = max(mx,sz - son[t]);
  if(mx <= mi) {
    root = t;
    mi = mx;
  }	
  vis[t] = false;
}
void dfs(int t,int mul,int ri) {
  vis[t] = true;
  //query
  mul =1LL *   mul * vi[t] % md;
  if(1LL * mul * ri % md == K) {
    pair<int ,int > tmp = pair<int ,int > (min(root,t),max(root,t));
    if(tmp < ans) ans = tmp;
  }
  int q = 1LL*  inv(1LL * mul * ri % md) * K  % md;
  if(vers[q] == verc && hash[q]!= 0 ) {
    pair<int ,int > tmp = pair<int ,int > (min(t,hash[q]),max(t,hash[q]));
    if(tmp < ans) ans = tmp;
  }
  son[t] = 1;
  for(int i = 0;i < edge[t].size();i ++) {
    int nxt = edge[t][i];
    if(!vis[nxt]) {
      dfs(nxt,mul,ri);
      son[t] += son[nxt];
    }
  }
  //set
  if(vers[mul] != verc ) {
    vers[mul] = verc;
    hash[mul] = t;
  }
  hash[mul] = min(hash[mul],t);
  vis[t] = false;
}
void work(int t,int sz) {
  mi = sz;
  getroot(t,sz);
  // dfs
  int rt = root;
  vis[rt] =true;
  verc ++;
  for(int i = 0;i <  edge[root].size();i ++) {
    int nxt = edge[rt][i];
    if(!vis[nxt]) {
      dfs(nxt,1,vi[rt] % md);
    }
  }
  for(int i = 0;i < edge[rt].size();i ++) {
    int nxt = edge[rt][i];
    if(!vis[nxt]) {
      work(nxt,son[rt]);
    }
  }
}
int main() {
  inv1();
  verc = 0;
  while(scanf("%d%d",&N,&K) != EOF) {
    init();		
    for(int i = 1;i <= N;i ++) {
      scanf("%d",&vi[i]);
    }
    for(int i = 0;i < N - 1;i ++) {
      int u,v;
      scanf("%d%d",&u,&v);
      add_edge(u,v);
      add_edge(v,u);
    }
    memset(vis,0,sizeof(vis));
    ans = pair<int ,int > (N+1,N+1);
    work(1,N);
    if(ans.first == N+1 && ans.second == N + 1) {
      puts("No solution");
    } else {
      printf("%d %d\n",ans.first,ans.second);
    }
  }
}
