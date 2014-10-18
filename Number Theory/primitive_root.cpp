struct PR {
  // make sure that p is prime
  // if p = 2, solve the prob. without PR
  int divs[N+5];
  int primitive_root(const int p) {
    if (p == 2) return 1;
    int cnt = 0, m = p-1;
    for (int i = 2; i*i <= m; ++ i) if (m%i == 0) {
      divs[cnt++] = i;
      if (i*i < m) divs[cnt++] = m/i;
    }
    int r = 2, j = 0;
    while (1) {
      for (j = 0; j < cnt; ++ j) {
        if (fastpow(r, divs[j], p) == 1) break;
      }
      if (j >= cnt) return r;
      r ++;
    }
    return -1;
  }
} pr_solver; 
