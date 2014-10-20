// get a factor of n in log(n)
LL Pollard_Rho(LL n, LL c=1) {
  LL i=1, k=2, x=rand()%(n-1)+1, y=x, d;
  while(1) {
    i++;
    x = (mul_mod(x,x,n)+c)%n;
    d=__gcd(n,y-x);
    if(d>1 && d<n) return d;
    if(y==x) return n;
    if(i==k){
      k<<=1;
      y=x;
    }
  }
}

