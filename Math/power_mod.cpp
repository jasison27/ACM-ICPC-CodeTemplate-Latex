// x^n = a (mod p), make sure that p is prime
// let g be a primitive root of p, x = g^y, a = g^m
// use log_mod to get m, g^(yn) = g^m (mod p)
// thus yn = m (mod p-1), use exgcd to solve and get back
vector<int> power_mod(int a, int n, int p) {
  int g = primitive_root(p);
  LL m = log_mod(g, a, p);
  vector<int>ret;
  if(a==0){
    ret.push_back(0);
    return ;
  }
  if(m==-1)return ret;
  LL A=n,B=p-1,C=m,x,y;
  LL d = exgcd(A,B,x,y);
  if(C%d!=0)return ret;
  x=x*(C/d)%B;
  LL delta=B/d;
  for(int i=0;i<d;++i){
    x=((x+delta)%B+B)%B;
    ret.push_back((int)pow_mod(g,x,p));
  }
  sort(ret.begin(),ret.end());
  ret.erase(unique(ret.begin(),ret.end()), ret.end());
  return ret;
}
