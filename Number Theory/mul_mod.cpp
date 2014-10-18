LL mul_mod(LL x, LL y, LL n) {
  LL T = floor(sqrt(n) + 0.5);
  LL t = T * T - n;
  LL a = x / T, b = x % T;
  LL c = y / T, d = y % T;
  LL e = a * c / T, f = a * c % T;
  LL v = ((a*d + b*c) % n + e*t) % n;
  LL g = v / T, h = v % T;
  LL ret = (((f+g)*t % n + b*d) % n + h*T) % n;
  return (ret % n + n) % n;
}

