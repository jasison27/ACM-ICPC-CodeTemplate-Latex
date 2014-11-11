// eg: soj 1066
const int N = 205;
int degree[N],n;
void init(){
	dicnic_solver.init();
	int m,a,b,c;
	scanf("%d%d",&n,&m);
	memset(degree,0,sizeof(degree));
	while(m--){
		// c=0,a<->b; c=1,a->b 
		scanf("%d%d%d",&a,&b,&c);
		a--; b--;
		degree[a]--;
		degree[b]++;
		if(!c)dicnic_solver.addEdge(a,b,1);
	}
}
bool work(){
	int ans=0;
	for(int i=0;i<n;++i)if(degree[i]&1)return 0;
	for(int i=0;i<n;++i){
		if(degree[i]<0){
			dicnic_solver.addEdge(n,i,-degree[i]/2);
			ans-=degree[i]/2;
		}else if(degree[i]>0){
			dicnic_solver.addEdge(i,n+1,degree[i]/2);
		}
	}
	return dicnic_solver.maxflow(n,n+1)>=ans;
}
void solve(){
	puts(work()?"possible":"impossible");
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		init();
		solve();
	}
	return 0;
}

