struct Matrix {
  int n, a[N][N];
  Matrix operator * (const Matrix &b) const {
    Matrix ret; ret.clear();
    ret.n = n;
    for (int i = 0; i < n; ++ i) {
      for (int k = 0; k < n; ++ k) if (a[i][k]) {
        for (int j = 0; j < n; ++ j) {
          ret.a[i][j] += a[i][k] * b.a[k][j];
          ret.a[i][j] %= mod;
        }
      }
    }
    return ret;
  }
  void clear() {
    memset(a,0,sizeof(a));
  }
};
Matrix matrix_one(int n) {
  Matrix ret; ret.clear();
  ret.n = n;
  for (int i = 0; i < n; ++ i) {
    ret.a[i][i] = 1;
  }
  return ret;
}
Matrix matrix_pow(Matrix x, int n) {
  Matrix ret = matrix_one(x.n), mul = x;
  while (n) {
    if (n&1) ret = ret * mul;
    mul = mul * mul;
    n >>= 1;
  }
  return ret;
}
