#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 5e3 + 5 , M = 5e4 + 5 , INF = 0x3f3f3f3f3f3f3f3fll;
int n , m , s , t , tot = 1 , head[N] , now[N];
ll dis[N];bool vis[N];
queue<int>q , eq;
struct Edge{ll to , nxt , f , c;}e[M * 2];
void Add(int u , int v , int w , int c)
{
	e[++tot] = {v , head[u] , w , c};
	head[u] = tot;
}
bool SPFA()
{
	memset(vis , 0 , sizeof vis);
	memset(dis , 0x3f , sizeof dis);
	memcpy(now , head , sizeof now);
	q = eq ; q.push(s); dis[s] = 0;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to , w = e[i].c;
			if(dis[u] + w < dis[v] && e[i].f > 0)
			{
				dis[v] = dis[u] + w;
				if(!vis[v])q.push(v) , vis[v] = 1;
			}
		}
	}
	return dis[t] != INF;
}
void Dinic(int u , ll flow , ll& f , ll& c)
{
	if(u == t){f = flow; c = 0;return ;}
	vis[u] = 1;
	ll rest = flow;
	for(int i = now[u] ; i && rest ; now[u] = i , i = e[i].nxt)
	{
		int v = e[i].to;
		if(!vis[v] && e[i].f && dis[v] == dis[u] + e[i].c)
		{
			ll k = 0 , w = 0;
			Dinic(v , min(rest , e[i].f) , k , w);
			if(!k)dis[v] = -INF;
			e[i].f -= k;
			e[i ^ 1].f += k;
			rest -= k;
			c += w + (ll)e[i].c * k;
		}
	}
	f = flow - rest;
	vis[u] = 0;
}
int main()
{
	scanf("%d%d%d%d" , &n , &m , &s , &t);
	for(int i = 1 ; i <= m ; i++)
	{
		int u , v , w , c;
		scanf("%d%d%d%d" , &u , &v , &w , &c);
		Add(u , v , w , c);
		Add(v , u , 0 , -c);
	}
	ll fg = 0 , cg = 0;
	while(SPFA())
	{
		ll f = 0 , c = 0;
		Dinic(s , INF , f , c);
		fg += f , cg += c;
	}
	printf("%lld %lld" , fg , cg);
	return 0;
}
