//HDU 3966
//operation1 path c1 to c2 plus k
//operation2 path c1 to c2 minus k
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
#define lc (o<<1)
#define rc (o<<1|1)
int N,M,P;
const int maxn = 100010;
vector<int > edge[maxn];
int ai[maxn];
void add_edge(int from,int to) {
  edge[from].push_back(to);
}
void init() {
  for(int i = 1;i <= N;i ++) edge[i].clear();
}
int son[maxn]; // size of children
int fa[maxn];
int wn[maxn]; //index in segment
int wcnt;
int vis[maxn];
int dep[maxn]; // depth
int top[maxn]; // link fa
//Tree link
void dfs1(int t,int d) {
  vis[t] = true;
  dep[t] = d;
  son[t] = 1;
  for(int i = 0;i < edge[t].size();i ++) {
    int nxt =  edge[t][i];
    if(!vis[nxt]) {
      fa[nxt] = t;
      dfs1(nxt,d + 1);
      son[t] += nxt;
    }
  }
  vis[t] = false;
}
void dfs2(int t) {
  vis[t] = true;
  wn[t] = wcnt ++;
  bool first = true;
  int index = -1;
  for(int i = 0;i < edge[t].size();i ++) {
    int nxt =  edge[t][i];
    if(!vis[nxt]) {
      if(first) {
        first  =false;
        index = nxt;
      }
      if(son[nxt] > son[index]) {
        index=  nxt;
      }
    }
  }
  if(!first ) {
    top[index] = top[t];
    dfs2(index);
    for(int i = 0;i < edge[t].size();i ++) {
      int nxt = edge[t][i];
      if(!vis[nxt] && nxt != index) {
        top[nxt] = nxt;
        dfs2(nxt);
      }
    }
  }
  vis[t] = false;
}
//segment tree
int addv[maxn << 2];
void add(int o,int l,int r,int y1,int y2,int v) {
  if(y1 <= l && r <= y2) {
    addv[o] += v;
  } else {
    int m =  (l + r) >> 1;
    if(y1 <= m) add(lc,l,m,y1,y2,v);
    if(m < y2) add(rc,m+1,r,y1,y2,v);
  }
}
void query(int o,int l,int r,int x,int  & ans) {
  if(l == r && r == x) {
    ans += addv[o];	
  } else {
    int m = (l + r ) >> 1;
    ans += addv[o];
    if(x <= m ) {
      query(lc,l,m,x,ans);
    } else {
      query(rc,m+1,r,x,ans);
    }
  }
}
void init_seg() {
  memset(addv,0,sizeof(addv));
}
char buff[5];
int main() {
  while(~scanf("%d%d%d",&N,&M,&P) ) {
    init();
    for(int i = 1;i <= N;i ++) {
      scanf("%d",&ai[i]);
    }
    for(int i = 0;i < M;i ++) {
      int u,v;
      scanf("%d%d",&u,&v);
      add_edge(u,v);
      add_edge(v,u);
    }	
    dfs1(1,1);
    wcnt = 0;
    top[1] = 1;
    dfs2(1);
    init_seg();
    while(P --) {
      scanf("%s",buff);
      if(buff[0] == 'I' || buff[0] == 'D') {
        int c1,c2,k;
        scanf("%d%d%d",&c1,&c2,&k);
        if(buff[0] == 'D') k = - k;
        /// query path
        while(top[c1] != top[c2]) {
          int f1 = top[c1];
          int f2 = top[c2];
          if(dep[f1] < dep[f2]) {
            swap(f1,f2);
            swap(c1,c2);
          }
          add(1,0,N - 1,wn[f1],wn[c1],k);
          c1 = fa[f1];
        }
        if(dep[c1] < dep[c2]) {
          swap(c1,c2);
        }
        add(1,0,N - 1,wn[c2],wn[c1],k);
      } else if(buff[0] == 'Q') {
        int d;
        scanf("%d",&d);
        int ans = 0;
        query(1,0,N-1,wn[d],ans);
        ans += ai[d];
        printf("%d\n",ans);
      }	
    }
  }
}


