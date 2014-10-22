// la 2659
#include <cstdio>
#include <vector>
using namespace std;
const int MROW = 16*16*16 + 5;
const int MCOL = 16*16*4 + 5;
const int NODE = 16*16*16*4 + 5;
struct DLX {
  int n, sz;
  int S[MCOL];
  int row[NODE], col[NODE];
  int ansd, ans[MROW];
  int L[NODE], R[NODE], U[NODE], D[NODE];
  void init(int n) {
    this->n = n;
    for (int i = 0; i <= n; ++ i) {
      U[i] = D[i] = i;
      L[i] = i-1; R[i] = i+1;
      S[i] = 0;
    }
    R[n] = 0; L[0] = n;
    sz = n+1;
  }
  void addRow(int r, const vector<int> &columns) {
    int first = sz;
    for (int i = 0; i < columns.size(); ++ i) {
      int c = columns[i];
      L[sz] = sz-1; R[sz] = sz+1;
      D[sz] = c; U[sz] = U[c];
      D[U[c]] = sz; U[c] = sz;
      row[sz] = r; col[sz] = c;
      S[c] ++; sz ++;
    }
    R[sz-1] = first; L[first] = sz-1;
  }
  #define FOR(i,A,s) for(int i=A[s];i!=s;i=A[i])
  void remove(int c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    FOR(i,D,c)
      FOR(j,R,i) { U[D[j]] = U[j]; D[U[j]] = D[j]; -- S[col[j]]; }
  }
  void restore(int c) {
    FOR(i,U,c)
      FOR(j,L,i) { ++S[col[j]]; U[D[j]]=j; D[U[j]]=j; }
    L[R[c]] = c; R[L[c]] = c;
  }
  bool dfs(int d) {
    if (R[0] == 0) {
      ansd = d;
      return 1;
    }
    int c = R[0];
    FOR(i,R,0) if(S[i]<S[c]) c=i;
    remove(c);
    FOR(i,D,c) {
      ans[d] = row[i];
      FOR(j,R,i) remove(col[j]);
      if(dfs(d+1)) return 1;
      FOR(j,L,i) restore(col[j]);
    }
    restore(c);
    return 0;
  }
  bool solve(vector<int>&v) {
    v.clear();
    if (!dfs(0)) return 0;
    for (int i = 0; i < ansd; ++ i) v.push_back(ans[i]);
    return 1;
  }
} dlx;
char data[18][18];
bool input() {
  for (int i = 0; i < 16; ++ i) {
    if (scanf("%s",data[i]) == EOF) return 0;
  }
  return 1;
}
enum { SLOT=0, ROW, COL, BLOK };
int encode(int i, int j, int k) {
  return i*256 + j*16 + k + 1;
}
int block(int i, int j) {
  return 4*(i/4) + (j/4);
}
void decode(int x, int &a, int &b, int &c) {
  x --;
  c = x % 16; x /= 16;
  b = x % 16; x /= 16;
  a = x;
}
vector<int>columns;
void solve() {
  dlx.init(16*16*4);
  for (int i = 0; i < 16; ++ i) {
    for (int j = 0; j < 16; ++ j) {
      for (int k = 0; k < 16; ++ k) {
        if (data[i][j] == '-' || data[i][j] == k+'A') {
          columns.clear();
          columns.push_back(encode(SLOT, i, j));
          columns.push_back(encode(ROW, i, k));
          columns.push_back(encode(COL, j, k));
          columns.push_back(encode(BLOK, block(i,j), k));
          dlx.addRow(encode(i,j,k), columns);
        }
      }
    }
  }
  columns.clear();
  dlx.solve(columns);
  for (int i = 0; i < columns.size(); ++ i) {
    int r, c, v;
    decode(columns[i], r, c, v);
    data[r][c] = char('A' + v);
  }
  for (int i = 0; i < 16; ++ i) {
    printf("%s\n", data[i]);
  }
}
int main() {
  int kcase = 0;
  while (input()) {
    if (kcase) puts("");
    kcase ++;
    solve();
  }
}

