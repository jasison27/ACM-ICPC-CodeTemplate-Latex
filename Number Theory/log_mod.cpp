// eg: hdu 2815
// d*a^(x-c) = b (mod n), make sure that (a,n) = 1 and (d,n) = 1
map<LL,LL>f;
LL log_mod(LL a, LL b, LL n, LL c, LL d) {
  LL m, v, e=1, i, x, y, dd;
  m = ceil( sqrt(n + 0.5) );
  f.clear();
  f[1] = m;
  for(i = 1; i < m; ++ i) {
    e = e*a%n;
    if (!f[e]) f[e] = i;
  }
  e = (e*a)%n;
  for (i = 0; i < m; ++ i) {
    exgcd(d,n,dd,x,y);
    x = (x*b%n + n) % n;
    if (f[x]) {
      LL num = f[x];
      return c + i*m + (num==m ? 0 : num);
    }
    d = (d*e) % n;
  }
  return -1;
}
// a^x = b (mod n), no restriction
LL log_mod(LL a, LL b, LL n) {
  b%=n;
  LL c = 0, d = 1, t;
  while((t=__gcd(a,n))!=1){
    if(b%t) return -1;
    c++;
    n/=t;
    b/=t;
    d=d*a/t%n;
    if(d==b)return c;
  }
  return log_mod(a,b,n,c,d);
}
