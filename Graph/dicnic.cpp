const int inf = 0x3f3f3f3f;
const int N = 205;
const int M = 1205;
struct Edge{
	int v,f,nxt;
};
struct Dicnic{
	int src,sink;
	int g[N],en;
	Edge e[M*2];
	int level[N];
	void _addEdge(int u,int v,int f){
		e[en].v=v;
		e[en].f=f;
		e[en].nxt=g[u];
		g[u]=en++;
	}
	void addEdge(int u,int v,int f){
		_addEdge(u,v,f);
		_addEdge(v,u,0);
	}
	void init(){
		en=0;
		memset(g,-1,sizeof(g));
	}
	int q[N],front,rear;
	bool bfs(){
		memset(level,0,sizeof(level));
		level[src]=1;
		front=0; rear=1;
		q[0]=src;
		while(front<rear){
			int u=q[front++];
			if(u==sink)return 1;
			for(int i=g[u];i!=-1;i=e[i].nxt){
				int v=e[i].v,f=e[i].f;
				if(!level[v]&&f){
					level[v]=level[u]+1;
					q[rear++]=v;
				}
			}
		}
		return 0;
	}
	int dfs(int u,int delta){
		if(u==sink)return delta;
		int ret=0;
		for(int i=g[u];i!=-1;i=e[i].nxt){
			int v=e[i].v, f=e[i].f;
			if(level[v]==level[u]+1&&f){
				int minf=min(delta-ret,f);
				f=dfs(v,minf);
				e[i].f-=f;
				e[i^1].f+=f;
				delta-=f;
				ret+=f;
				if(ret==delta)return ret;
			}
		}
		return ret;
	}
	int maxflow(int _src,int _sink){
		src=_src;
		sink=_sink;
		int ret=0;
		while(bfs())ret+=dfs(src,inf);
		return ret;
	}
}dicnic_solver;
