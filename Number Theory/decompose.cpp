struct Factor{ // factor as p^num
	LL p;
	int num;
}; 
struct DeComposer {
	DeComposer() {
		process();
	}
	LL prime[maxn];
	bool isprime[maxn+5]={0};
	int pn;
	void process() { // primes less than sqrt(MAX)
	  pn = 0;
	  for(LL i = 2; i <= maxn; ++ i) {
	    if(!isprime[i]) prime[pn++] =i;
	    for(LL j=i*i; j <= maxn; j += i) isprime[j] = 1;
	  }
	}
	Factor fc[64];
	int fcn, fn;
	LL factor[100000]; // all factors
	void decompose2(LL x,int d){
	  if(d==fcn){
	    factor[fn++] = x;
	  } else {
	    for(int i = 0; i <= fc[d].num; ++ i) {
	      decompose2(x, d+1);
	      x *= fc[d].p;
	    }
	  }
	}
	void decompose1(LL x) {
	  fcn = 0;
	  for(int i = 0; i < pn && prime[i] * prime[i] <= x; ++ i) if (x % prime[i] == 0) {
	    fc[fcn].p = prime[i];
	    fc[fcn].num = 0;
	    while(x % prime[i] == 0) {
	      fc[fcn].num ++;
	      x /= prime[i];
	    }
	    fcn ++;
	  }
	  if (x > 1) {
	    fc[fcn].p = x;
	    fc[fcn].num = 1;
	    fcn ++;
	  }
	}
	void decompose(LL x){
	  decompose1(x);
	  fn = 0;
	  decompose2(1,0);
	}
} dc_solver;
