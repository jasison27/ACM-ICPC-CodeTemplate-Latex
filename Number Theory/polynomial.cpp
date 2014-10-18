struct Poly {
  double coef[MAXN];
  int n;
  Poly(int _n  = 0) : n(_n) {
    for(int i = 0; i < MAXN; ++ i) coef[i] = 0;
  }
  Poly operator + (const Poly &a) {
    Poly ret(max(n, a.n));
    for (int i = ret.n; i >= 0; i--) {
      ret.coef[i] = coef[i] + a.coef[i];
    }
    while (sgn(ret.coef[ret.n]) == 0 && ret.n) ret.n--;
    return ret;
  }
  Poly operator - (const Poly &a) {
    Poly ret(max(n, a.n));
    for (int i = ret.n; i >= 0; i--) {
      ret.coef[i] = coef[i] - a.coef[i];
    }
    while (sgn(ret.coef[ret.n]) == 0 && ret.n) ret.n--;
    return ret;
  }
  Poly operator * (const Poly &a) {
    Poly ret(n + a.n);
    for (int i = n; i >= 0; i--) {
      for (int j = a.n; j >= 0; j--) {
        ret.coef[i + j] += coef[i] * a.coef[j];
      }
    }
    return ret;
  }
  Poly operator / (const Poly &a) {
    if (n < a.n) return *this;
    Poly ret(n - a.n);
    for (int i = ret.n; i >= 0; i--) {
      ret.coef[i] = coef[i + a.n];
    }
    for (int i = ret.n; i >= 0; i--) {
      ret.coef[i] /= a.coef[a.n];
      for (int j = i - 1; a.n - i + j >= 0 && j >= 0; j--) {
        ret.coef[j] -= ret.coef[i] * a.coef[a.n - i + j];
      }
    }
    return ret;
  }
  Poly operator % (const Poly &a) {
    Poly ret = *this - *this / a * a;
    while (sgn(ret.coef[ret.n]) == 0 && ret.n) ret.n--;
    return ret;
  }
};
Poly gcd(Poly a , Poly b) {
  if (b.n == 0 && sgn(b.coef[0]) == 0) return a;
  else return gcd(b, a % b);
}

