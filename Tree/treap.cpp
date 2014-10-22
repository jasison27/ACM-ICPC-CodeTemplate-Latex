struct Node {
  Node *ch[2]; // 0-left 1-right
  int r, v, s; // rank, val, #node
  Node(int v): v(v) {
    ch[0] = ch[1] = NULL;
    r = rand();
    s = 1;
  }
  int cmp(int x) const {
    if (x == v) return -1;
    return x < v ? 0 : 1;
  }
  void maintain() { // maintain #node
    s = 1;
    if (ch[0] != NULL) s += ch[0]->s;
    if (ch[1] != NULL) s += ch[1]->s;
  }
};
void rotate(Node* &o, int d) {
  Node* k = o->ch[d^1];
  o->ch[d^1] = k->ch[d];
  k->ch[d] = o;
  o->maintain();
  k->maintain();
  o = k;
}
void insert(Node* &o, int x) {
  if (o == NULL) {
    o = new Node(x);
  } else {
    int d = o->cmp(x);
    if (d != -1) {  // same ele won't be inserted
      insert(o->ch[d], x);
      if (o->ch[d]->r > o->r) rotate(o, d^1);
    }
  }
  o->maintain();
}
void remove(Node* &o, int x) {
  if (o == NULL) return ; // ele to be removed not exist
  int d = o->cmp(x);
  if (d == -1) {
    Node* ret = o;
    if (o->ch[0] != NULL && o->ch[1] != NULL) {
      int d2 = (o->ch[0]->r > o->ch[1]->r ? 1 : 0);
      rotate(o, d2);
      remove(o->ch[d2], x);
    } else {
      if (o->ch[0] == NULL) o = o->ch[1];
      else o = o->ch[0];
      delete ret;
    }
  } else {
    remove(o->ch[d], x);
  }
  if (o) o->maintain();
}
int find(Node* o, int x) {
  while (o != NULL) {
    int d = o->cmp(x);
    if (d == -1) return 1;
    else o = o->ch[d];
  }
  return 0;
}
int kth_big(Node* o, int k) {
  if (o == NULL || k <= 0 || k > o->s) return 0;
  int s = o->ch[1] == NULL ? 0 : o->ch[1]->s;
  if (k == s+1) return o->v;
  else if (k <= s) return kth_big(o->ch[1], k);
  else return kth_big(o->ch[0], k-s-1);
}
int kth_small(Node* o, int k) {
  if (o == NULL || k <= 0 || k > o->s) return 0;
  int s = o->ch[0] == NULL ? 0 : o->ch[0]->s;
  if (k == s) return o->v;
  else if (k < s) return kth_small(o->ch[0], k);
  else return kth_small(o->ch[1], k-s-1);
}
void merge(Node* &src, Node* &dest) {
  if (src == NULL) return ;
  merge(src->ch[0], dest);
  merge(src->ch[1], dest);
  insert(dest, src->v);
  delete src;
  src = NULL;
}
void clear(Node* &o) {
  if (o == NULL) return ;
  clear(o->ch[0]);
  clear(o->ch[1]);
  delete o;
  o = NULL;
}

