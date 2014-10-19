// prime test
bool Witness(LL n, LL a) {
  LL m = n-1, j = 0;
  while(!(m&1)) m >>= 1, j ++;
  LL ans = pow_mod(a, m, n);
  while (j --) {
    LL tmp = mul_mod(ans, ans, n);
    if (tmp == 1 && ans != 1 && ans != n-1) return 1;
    ans = tmp;
  }
  return ans != 1;
}
bool Miller_Rabin(LL n) {
  if (n < 2) return 0;
  if (n == 2) return 1;
  if (!(n&1)) return 0;
  for (int i = 0; i < max_test; ++ i) {
    ll a = rand() % (n-2) + 2;
    if (Witness(n,a)) return 0;
  }
  return 1;
}

