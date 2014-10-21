// a * x + b * y = d, |x| + |y| get the minimum
LL exgcd(LL a, LL b, LL &d, LL &x, LL &y){
  if (a) { x = 0; y = 1; return a; }
  else { exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
