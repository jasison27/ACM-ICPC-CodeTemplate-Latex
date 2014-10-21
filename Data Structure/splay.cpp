#include <cstdio>
#include <iostream>
using namespace std;
struct Node {
  Node* ch[2];
  int v, s, flip;
  void maintain() {
    s = 1 + ch[0]->s + ch[1]->s;
  }
  void pushdown() {
    if (flip) {
      flip = 0;
      swap(ch[0], ch[1]);
      ch[0]->flip ^= 1;
      ch[1]->flip ^= 1;
    }
  }
  int cmp(int k) const {
    int d = k - ch[0]->s;
    if (d == 1) return -1;
    return d <= 0 ? 0 : 1;
  }
};
Node* null = new Node();
void rotate(Node* &o, int d) {
  Node* k = o->ch[d^1];
  o->ch[d^1] = k->ch[d];
  k->ch[d] = o;
  o->maintain();
  k->maintain();
  o = k;
}
void splay(Node* &o, int k) {
  o->pushdown();
  int d = o->cmp(k);
  if (d == 1) k -= o->ch[0]->s + 1;
  if (d != -1) {
    Node* p = o->ch[d];
    p->pushdown();
    int d2 = p->cmp(k);
    int k2 = (d2 == 0) ? k : k - p->ch[0]->s - 1;
    if (d2 != -1) {
      splay(p->ch[d2], k2);
      if (d == d2) {
        rotate(o, d^1);
      } else {
        rotate(o->ch[d], d);
      }
    }
    rotate(o, d^1);
  }
}
Node* merge(Node* left, Node* right) { // make sure left != null
  splay(left, left->s);
  left->ch[1] = right;
  left->maintain();
  return left;
}
void split(Node* o, int k, Node* &left, Node* &right) { // make sure 1 <= k <= o->s
  splay(o, k);
  left = o;
  right = o->ch[1];
  o->ch[1] = null;
  left->maintain();
}
const int maxn = 300000 + 10;
struct SS {
  int n;
  Node seq[maxn];
  Node* root;
  Node* build(int sz) {
    if (!sz) return null;
    Node* L = build(sz/2);
    Node* o = &seq[++n];
    o->v = n-1;
    o->flip = 0;
    o->ch[0] = L;
    o->ch[1] = build(sz - sz/2 - 1);
    o->maintain();
    return o;
  }
  void init(int sz) {
    n = 0;
    null->s = null->flip = 0;
    root = build(sz);
  }
  void print(Node *o) {
    if (o != null) {
      o->pushdown();
      print(o->ch[0]);
      if (o->v) {
        if (o->v != 1) putchar(' ');
        printf("%d", o->v);
      }
      print(o->ch[1]);
    }
  }
} ss;
int n, m, a, b, c;
char op[10];
int main() {
  while (scanf("%d%d",&n,&m) == 2 && n != -1 && m != -1) {
    ss.init(n+1);
    Node *t1, *t2, *t3;
    while(m--){
      scanf("%s",op);
      if(op[0]=='C'){ // split [a,b], put it after c
        scanf("%d%d%d",&a,&b,&c);
        split(ss.root, b+1, t1, t2);
        split(t1, a, t1, t3);
        ss.root = merge(t1, t2);
        split(ss.root, c+1, t1, t2);
        ss.root = merge(merge(t1, t3), t2);
      } else { // flip [a,b]
        scanf("%d%d",&a,&b);
        split(ss.root, b+1, t1, t3);
        split(t1, a, t1, t2);
        t2->flip ^= 1;
        ss.root = merge(merge(t1, t2), t3);
      }
    }
    ss.print(ss.root);
    puts("\n");
  }
}
