LL inv1(LL a, LL n) {
  LL d, x, y;
  gcd(a,n,d,x,y);
  return d == 1 ? (x+n)%n : -1;
}
LL inv2(LL a, LL p) { // in case that p is a prime
  return pow_mod(a, p-2, p);
}

