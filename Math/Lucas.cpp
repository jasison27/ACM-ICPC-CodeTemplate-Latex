// C(n,m) % p, make sure p is prime, p <= 10^5
// n = n[k] * p^k + n[k-1] * p^(k-1) + .. + n[0]
// m = m[k] * p^k + m[k-1] * p^(k-1) + .. + m[0]
// then, C(n,m) = C(n[k],m[k])*C(n[k-1],m[k-1])*..*C(n[0],m[0]) (mod p)
// C(n,m) = C(n%p, m%p) * C(n/p, m/p) (mod p)
// eg: hdu3037
LL Lucas(LL n, LL m, LL p) {
  LL ret = 1;
  while(n && m) {
    LL np = n%p, mp = m%p;
    if(np < mp) return 0;
    ret = ret * factorial(np) % p * reverse(factorial(mp), p) % p * reverse(factorial(np-mp), p) % p;
    n /= p;
    m /= p;
  }
  return ret;
}
