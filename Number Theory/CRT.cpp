LL CRT(const vector<LL>&m, const vector<LL> &b){
  bool flag = false;
  LL x, y, i, d, result, a1, m1, a2, m2, Size = m.size();
  m1 = m[0], a1 = b[0];
  for(int i = 1; i < Size; i++){
    m2 = m[i], a2 = b[i];
    d = exgcd(m1, m2, x, y);
    if ((a2 - a1) % d != 0) flag = true;
    result = (mod_mul(x, (a2 - a1) / d, m2) % m2 + m2) % m2;
    LL tmp = m1;
    m1 = m1 / d * m2;
    a1 = (a1 + mod_mul(tmp, result, m1)) % m1;
    a1 = (a1 % m1 + m1) % m1;
  }
  if (flag) return -1;
  else return a1;
}
