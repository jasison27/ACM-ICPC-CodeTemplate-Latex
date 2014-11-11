// eg: soj 1013
const int N = 105;
const int inf = 1000000000;
struct KM{
	int w[N][N],x[N],y[N];
	int px[N],py[N],sy[N],sk[N],pr[N];
	int lx,ly,n;
	void adjust(int v){
		sy[v]=py[v];
		if(px[sy[v]]!=-2)adjust(px[sy[v]]);
	}
	int solve(int _n,int _w[][N]){
		n=_n;
		memcpy(w,_w,sizeof(w));
		return km();
	}
	bool find(int v){
		for(int i=0;i<n;++i)if(py[i]==-1){
			if(sk[i]>x[v]+y[i]-w[v][i]){
				sk[i]=x[v]+y[i]-w[v][i];
				pr[i]=v;
			}
			if(x[v]+y[i]==w[v][i]){
				py[i]=v;
				if(sy[i]==-1){
					adjust(i);
					return 1;
				}
				if(px[sy[i]]!=-1)continue;
				px[sy[i]]=i;
				if(find(sy[i]))return 1;
			}
		}
		return 0;
	}
	int km(){
		int i,j,m;
		for(i=0;i<n;++i){
			sy[i]=-1;
			y[i]=0;
		}
		for(i=0;i<n;++i){
			x[i]=0;
			for(j=0;j<n;++j){
				x[i]=max(x[i],w[i][j]);
			}
		}
		bool f;
		for(i=0;i<n;++i){
			for(j=0;j<n;++j){
				px[j]=py[j]=-1;
				sk[j]=inf;
			}
			px[i]=-2;
			if(find(i))continue;
			f=0;
			while(!f){
				m=inf;
				for(j=0;j<n;++j)if(py[j]==-1)m=min(m,sk[j]);
				for(j=0;j<n;++j){
					if(px[j]!=-1)x[j]-=m;
					if(py[j]!=-1)y[j]+=m;else sk[j]-=m;
				}
				for(j=0;j<n;++j)if(py[j]==-1&&!sk[j]){
					py[j]=pr[j];
					if(sy[j]==-1){
						adjust(j);
						f=1;
						break;
					}
					px[sy[j]]=j;
					if(find(sy[j])){
						f=1;
						break;
					}
				}
			}
		}
		int ans=0;
		for(i=0;i<n;++i)ans+=w[sy[i]][i];
		return ans;
	}
}km_solver;

