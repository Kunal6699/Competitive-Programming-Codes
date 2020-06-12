//problem link:-https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/practice-problems/algorithm/sherlock-and-highways/
#include<bits/stdc++.h>
#define ll long long 
#define scn(n) scanf("%d",&n)
#define lscn(n) scanf("%lld",&n)
#define lpri(n) printf("%lld",n)
#define pri(n) printf("%d",n)
#define pln() printf("\n")
#define priln(n) printf("%d\n",n)
#define lpriln(n) printf("%lld\n",n)
#define rep(i,init,n) for(int i=init;i<n;i++)
#define pb push_back     
#define mp make_pair
#define F first
#define S second
#define gcd __gcd
#define inf INT_MAX
#define ninf INT_MIN
using namespace std;
const ll mod=1e9+7;         
const int N=2e5+4;

vector<int> ve[N],tree[N];

int u[N],v[N];

int tim=0,low[N],num[N],par[N],bridges=0;

bool visit[N];

int find(int node)
{
    par[node]=(par[node]==node)?node:find(par[node]);
    
    return par[node];
}

void merge(int i,int j)
{
    int pi=find(i),pj=find(j);
    
    if(pi==pj)
    return;
    
    par[pi]=pj;
}

void dfs(int node,int e)
{
    visit[node]=1;
    
    low[node]=num[node]=tim++;
    
    for(int it:ve[node])
    if(it!=e)
    {
        int here=node^u[it]^v[it];
            
        if(!visit[here])
        {
            dfs(here,it);
            
            low[node]=min(low[node],low[here]);        
        }
        else 
        low[node]=min(low[node],num[here]);
    }
    
    if(e!=-1)
    {
        if(low[node]==num[node])
        bridges++;
        else
        merge(u[e],v[e]);
    }
}

int diameter=0;

int dfs_util(int node)
{
    visit[node]=1;
    
    int mx1=0,mx2=0;
    
    for(int it:tree[node])
    if(!visit[it])
    {
        int here=dfs_util(it)+1;
        
        if(here>=mx1)
        {
            mx2=mx1;
            
            mx1=here;
        }
        else if(here>mx2)
        mx2=here;
    }
    
    diameter=max(diameter,mx1+mx2);
    
    return mx1;
}

void bridge_tree(int n,int m)
{
    rep(i,1,n+1)
    par[i]=i;
    
    rep(i,1,n+1)
    if(!visit[i])
    dfs(i,-1);
    
    int root=0;
    
    rep(i,0,m)
    {
        int pa=find(u[i]),pb=find(v[i]);
        
        if(pa!=pb)
        {
            tree[pa].pb(pb);
            
            tree[pb].pb(pa);
            
            root=pa;
        }
    }
    
    memset(visit,0,sizeof(visit));
    
    dfs_util(root);
}

int main()
{
    int n,m;
    
    scn(n);  scn(m);
    
    rep(i,0,m)
    {
        scn(u[i]);  scn(v[i]);
        
        ve[u[i]].pb(i);
        
        ve[v[i]].pb(i);
    }
    
    bridge_tree(n,m);
    
    printf("%d %d",bridges,diameter);
    
    return 0;
}