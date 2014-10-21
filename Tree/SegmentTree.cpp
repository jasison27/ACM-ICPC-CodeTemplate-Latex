//HDU 4578
//segment  plus mul power sum 
#include <cstdio>
#include <algorithm>
using namespace std;
#define lc (o<<1)
#define rc (o<<1|1)
const int maxn = 100010;
const int md = 10007;
int sumv1[maxn<<2], sumv2[maxn<<2], sumv3[maxn<<2];
int addv[maxn<<2], setv[maxn<<2], timv[maxn<<2];
void pushdown(int o) {
  if (setv[o] >= 0) {
    setv[lc] = setv[rc] = setv[o];
    addv[lc] = addv[rc] = 0;
    timv[lc] = timv[rc] = 1;
    setv[o] = -1;
  }
  if (timv[o] != 1) {
    addv[lc] *= timv[o];
    addv[lc] %= md;
    addv[rc] *= timv[o];
    addv[rc] %= md;
    timv[lc] *= timv[o];
    timv[lc] %= md;
    timv[rc] *= timv[o];
    timv[rc] %= md;
    timv[o] = 1;
  }
  if (addv[o] > 0) {
    addv[lc] += addv[o];
    addv[lc] %= md;
    addv[rc] += addv[o];
    addv[rc] %= md;
    addv[o] = 0;
  }
} 
void maintain(int o,int l,int r) {
  if (l == r) {
    if (setv[o] != -1) {
      sumv1[o] = setv[o];
      setv[o] = -1;
    }
    if (timv[o] != 1) {
      sumv1[o] *= timv[o];
      timv[o] = 1;
      sumv1[o] %= md;
    }
    if (addv[o] > 0) {
      sumv1[o] += addv[o];
      sumv1[o] %= md;
      addv[o] = 0;
    }
    sumv2[o] = sumv1[o] * sumv1[o] % md;
    sumv3[o] = sumv1[o] * sumv2[o] % md;
  } else {
    sumv1[o] = (sumv1[lc] + sumv1[rc]) % md;
    sumv2[o] = (sumv2[lc] + sumv2[rc]) % md;
    sumv3[o] = (sumv3[lc] + sumv3[rc]) % md;
    if (setv[o] != -1) {
      sumv1[o] = setv[o] * (r - l +1) % md;
      sumv2[o] = setv[o] * setv[o] % md * (r - l + 1) % md;
      sumv3[o] = setv[o] * setv[o] % md * setv[o] % md * (r - l + 1) % md;
    }
    if (timv[o] != 1) {
      sumv1[o] *= timv[o];
      sumv1[o] %= md;
      sumv2[o] *= timv[o] * timv[o] % md;
      sumv2[o] %= md;
      sumv3[o] *= timv[o] * timv[o] % md * timv[o] % md;
      sumv3[o] %= md;
    }
    if (addv[o] > 0) {
      int tmp1 = sumv1[o];
      sumv1[o] += addv[o] * (r - l + 1) % md;
      sumv1[o] %= md;
      int tmp2 = sumv2[o];
      int tmp3 = sumv3[o];
      sumv2[o] = (tmp2 + 2*tmp1%md * addv[o]%md + addv[o] * addv[o] %md* (r - l  +1)%md) % md; 
      sumv3[o] = tmp3 + 3 * tmp2%md * addv[o] % md + 3 * tmp1 % md * addv[o]%md * addv[o] % md + addv[o] * addv[o] % md * addv[o] % md * (r - l  + 1) %md;
      sumv3[o] %= md;
    }
  }
}
void setq(int o,int l,int r,int y1,int y2,int v) {
  if (y1 <= l && r <= y2) {
    setv[o] = v;
    addv[o] = 0;
    timv[o] = 1;
  } else {
    pushdown(o);
    int m = (l + r) >> 1;
    if (y1 <= m) setq(lc,l,m,y1,y2,v);
    else maintain(lc,l,m);
    if (m < y2) setq(rc,m+1,r,y1,y2,v);
    else maintain(rc,m+1,r);
  }
  maintain(o,l,r);
}
void addq(int o,int l,int r,int y1,int y2,int v) {
  if (y1 <= l && r <= y2) {
    addv[o] += v;
    addv[o] %= md;
  } else {
    pushdown(o);
    int m = (l +r) >> 1;
    if (y1 <= m ) addq(lc,l,m,y1,y2,v);
    else maintain(lc,l,m);
    if (m < y2) addq(rc,m+1,r,y1,y2,v);
    else maintain(rc,m+1,r);
  }
  maintain(o,l,r);
}
void timq(int o,int l,int r,int y1,int y2,int v) {
  if (y1 <= l && r <= y2) {
    timv[o] *= v;
    timv[o] %= md;
    addv[o] *= v;
    addv[o] %= md;        
  } else {
    pushdown(o);
    int m = (l + r) >> 1;
    if (y1 <= m) timq(lc,l,m,y1,y2,v);
    else maintain(lc,l,m);
    if (m < y2) timq(rc,m+1,r,y1,y2,v);
    else maintain(rc,m+1,r);
  }
  maintain(o,l,r);
}
int ans1, ans2, ans3;
void query(int o,int l,int r,int y1,int y2,int add,int ti) {
  if (setv[o] > 0) {
    add = ti * addv[o] % md + add;
    ti = ti * timv[o] % md;
    int len = min(r,y2) - max(y1,l) + 1;
    int tmp1 = setv[o] * len % md * ti % md;
    int tmp2 = setv[o] * setv[o] % md * len % md * ti%md * ti %md;
    int tmp3 = setv[o] * setv[o] % md * setv[o] % md * len % md *ti %md* ti % md* ti % md;
    int _sum1 = tmp1 + add * len % md;
    _sum1 %= md;
    int _sum2 = (tmp2 + 2* tmp1 * add % md + add * add % md * len % md) % md;
    int _sum3 = (tmp3 + 3 * tmp2 * add % md + 3 * tmp1 * add % md * add % md + len * add % md * add % md *add % md) % md;
    ans1 = (ans1 + _sum1) % md;
    ans2 = (ans2 + _sum2) % md;
    ans3 = (ans3 + _sum3) % md;
    return ;
  }
  if (y1 <= l && r <= y2) {
    int tmp1 = sumv1[o] * ti % md;
    int tmp2 = sumv2[o] * ti % md * ti % md;
    int tmp3 = sumv3[o] * ti % md * ti % md * ti % md;
    int _sum =  tmp1 + add * (r - l + 1) % md;
    int _sum2 = tmp2 + 2* tmp1 * add % md + add * add % md * (r - l + 1) % md;
    int _sum3 = tmp3 + 3 * tmp2 % md * add % md + 3 * tmp1 % md * add % md * add % md + add * add % md * add % md * (r- l + 1) % md;
    _sum %= md;
    _sum2 %= md;
    _sum3 %= md;
    ans1 = (ans1 + _sum) % md;
    ans2 = (ans2 + _sum2) % md;
    ans3 = (ans3 + _sum3) % md;

  } else {
    int m = (l +r ) >> 1;
    if (y1 <= m) query(lc,l,m,y1,y2,(ti * addv[o] % md + add) % md,ti * timv[o] % md);
    if (m < y2) query(rc,m+1,r,y1,y2,(ti * addv[o] % md + add) % md,ti * timv[o] % md);
  }
}
void init(int o,int l,int r) {
  setv[o] = -1;
  timv[o] = 1;
  addv[o] = 0;
  sumv1[o] = sumv2[o] = sumv3[o] = 0; 
  if (l == r) {
  } else {
    int m = (l + r) >> 1;
    init(lc,l,m);
    init(rc,m+1,r);
  }
}
int main() {
  int N,M;
  while (scanf("%d%d",&N,&M)==2 && N && M) {
    init(1,1,N);
    while (M --) {
      int cmd,x,y,c;
      scanf("%d%d%d%d",&cmd,&x,&y,&c);
      if(cmd == 1) {
        c %= md;
        addq(1,1,N,x,y,c);
      } else if(cmd == 2) {
        c %= md;  
        timq(1,1,N,x,y,c);
      } else if(cmd == 3) {
        c %= md;  
        setq(1,1,N,x,y,c);
      } else if(cmd == 4) {
        ans1 = ans2 = ans3 = 0;
        query(1,1,N,x,y,0,1);
        if(c == 1) {
          printf("%d\n",ans1);
        } else if(c == 2){
          printf("%d\n",ans2);    
        } else if(c == 3) {
          printf("%d\n",ans3);    
        }
      }
    }
  }
}

