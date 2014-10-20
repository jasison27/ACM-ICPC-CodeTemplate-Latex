// ax = b (mod n)
// let d = gcd(a,n), use exgcd to solve ax + ny = d
// if b|d, then there are #ans=d, otherwise, no solution
vector<LL> line_mod(LL a, LL b, LL n) {
  LL x, y;
  exgcd(a,n,x,y);
  vector<LL>ans;
  ans.clear();
  if(b%d==0){
    x%=n; x+=n; x%=n;
    ans.push_back(x*(b/d)%(n/d));
    for(LL i=1;i<d;++i){
      ans.push_back((ans[0]+i*n/d)%n);
    }
  }
  return ans;
}
