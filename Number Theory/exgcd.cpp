// a * x + b * y = 1
LL exgcd(LL a, LL b, LL &x, LL &y){
  if (!a){
    x = 0;
    y = 1;
    return b;
  }
  LL g = exgcd(b % a, a, x, y);
  LL t = y;
  y = x;
  x = t - (b / a) * y;
  return g;
}
