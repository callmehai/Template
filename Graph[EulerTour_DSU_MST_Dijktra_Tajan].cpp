struct EulerTour{
    int n;
    vt<int> A;
    vt<int> end;
    vt<int> pos;
    vt<vt<int>> nxt;
    int flag=0;
    EulerTour(int _){
        n=_;
        A.resize(n+1);
        end.resize(n+1);
        pos.resize(n+1);
        nxt.resize(n+1);
    }
    void build(int u){
        pos[u]=++flag;
        A[flag]=u;
        for(int v : nxt[u]){
            build(v);
        }
        end[u]=flag;
    }
};
struct DSU {
    int n;
    int cnt;
    vector<int> pa;
    DSU(int _n) {
        n = _n;
        cnt=n;
        pa.resize(n+1,-1);
    }
    int root(int u) {
        return pa[u] < 0 ? u : pa[u] = root(pa[u]);
    }
    int group_count(){
        return cnt;
    }
    int count(int u){
        return -pa[root(u)];
    }
    bool share(int u,int v){
        return root(u) == root(v);
    }
    bool merge(int u, int v) {
        u = root(u); v = root(v);
        if (u == v) return 0;
        if(pa[u] > pa[v]) swap(u,v);
        pa[u]+=pa[v]; pa[v]=u;
        cnt--;
        return 1;
    }
};
long long MST(vector<pair<int,pair<int,int>>> &e,int n) { // return MST and its total cost
   sort(e.begin(),e.end());
   vector<pair<int,pair<int,int>>> ans;
   long long res = 0;
   DSU dsu(n);
   for (auto edge: e) {
       int u = edge.second.first, v = edge.second.second, p = edge.first;
       if (dsu.merge(u, v)) {
           ans.push_back(edge);
           res += p;
       }
   }
   e = ans;
   return res;
}
void Dijktra(int st,vt<vt<int>> Edge, vt<int> &dis)
{
    dis[st]=0;
    priority_queue<pii,vt<pii>,greater<pii>> pq;
    pq.push({0,st});
    while(!pq.empty())
    {
        pii k=pq.top(); pq.pop();
        int u = k.se, w = k.fi;
        
        if (w > dis[u]) continue;

        for(auto &v: Edge[u]) {
           if (dis[v] > w + 1) {
               dis[v] = 1 + w;
               pq.push({dis[v], v});
           }
        }
    }
}
// 2SAT 
int notP(int u){
    if(u<=n) return u+n;
    return u-n;
}

struct Tajan{
    int n,cnt,timeDFS;
    vt<int> num,low,id,st;
    vt<vt<int>> ke;

    Tajan(int _){
        n=_;
        cnt=0;
        timeDFS=0;
        num.resize(n+1);
        low.resize(n+1);
        id.resize(n+1,0);
        st.resize(n+1);
        ke.resize(n+1);
        for(int i=1;i<=n;i++) ke[i].clear();
    }
    void dfs(int u){
        num[u] = low[u] = ++timeDFS;
        st[++st[0]]=u;
        for(int &v : ke[u]){
            if(id[v]) continue;
            if(num[v]==0){
                dfs(v);
                low[u]=min(low[u],low[v]);
            }
            else{
                low[u]=min(low[u],num[v]);
            }
        }
        
        if(num[u]==low[u]){
            cnt++;
            while(true){
                int v = st[st[0]--];
                id[v]=cnt;
                if(v==u) break;
            }
        }
        
    }
    void build(){
        for(int i=1;i<=n;i++) if(!id[i]){
            dfs(i);
        }
    }
};
