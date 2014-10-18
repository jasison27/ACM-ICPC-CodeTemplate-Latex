LL pow_mod(LL a, LL x, LL n) {
  LL ret = 1, mul = a;
  while (x) {
    if (x&1) ret = mul_mod(ret, mul, n);
    mul = mul_mod(mul, mul, n);
    x >>= 1;
  }
  return ret;
}
