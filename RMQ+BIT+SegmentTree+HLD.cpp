const int N=2e5+5;
int n;
int a[N];
struct RMQ
{
    int f[20][N],lg[N],x;
    void init()
    {
        for(int i=1;i<=n;i++) 
        {
            lg[i]=lg[i>>1]+(i>1);
            f[0][i]=a[i];
        }
        for(int i=1;(1<<i)<=n;i++)
            for(int j=1;j+(1<<(i-1))<=n;j++)
                f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
    }
    int query(int l,int r)
    {
        if(l>r) swap(l,r);
        x=lg[r-l];
        return min(f[x][l],f[x][r-(1<<x)+1]);
    }
};

struct BIT{ // getmax
    vt<int> A;
    int n;
    BIT(int _){
        n=_;
        A.resize(n+1,0);
    }
    void up(int x,int val)
    {
        for(int i=x;i<=n;i+=(i&(-i))){
            maximize(A[i],val);
        }
    }
    int get(int x){
        int ans=0;
        for(int i=x;i>0;i-=(i&(-i))){
            maximize(ans,A[i]);
        }
        return ans;
    }
};

struct SegmentTree{
    
    vt<ll> A;
    vt<ll> Lazi;
    int n;
    
    void newSegmentTree(int _){
        n=_;
        A.resize(n<<2);
        Lazi.resize(n<<2);
    }
    void down(int id)
        {
        ll val=Lazi[id];
        Lazi[id]=0;
        
        id*=2;
        
        A[id]+=val;
        A[id+1]+=val;
        
        Lazi[id]+=val;
        Lazi[id+1]+=val;
        
        
        
    }
    void up(int id,int l,int r,int u,int v,ll val)
    {

        if(l>v || r<u) return;
        if(l>=u && r<=v){
            Lazi[id]+=val;
            A[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        down(id);
        up(id*2,l,mid,u,v,val);
        up(id*2+1,mid+1,r,u,v,val);
    }
    ll get(int id,int l,int r,int u)
    {
        if(l==r)
        {
            return A[id];
        }
        down(id);
        int mid=(l+r)/2;
        if(u<=mid) return get(id*2,l,mid,u);
        else return get(id*2+1,mid+1,r,u);
        
    }
};
struct HLD{
    
    int n;
    int cnt_chain;
    int size;
    int flag;
    vt<vt<int>> Edge;
    vt<int> pa;
    vt<int> child;
    vt<int> chain;
    vt<int> head;
    vt<int> pos;
    vt<int> end;
    vt<ll> weight;
    vt<ll> sum;
    SegmentTree myTree;
    HLD(int _){
        n=_;
        cnt_chain=1;
        size=0;
        Edge.resize(n+1);
        pa.resize(n+1);
        child.resize(n+1);
        chain.resize(n+1);
        head.resize(n+1,0);
        pos.resize(n+1);
        end.resize(n+1);
        weight.resize(n+1);
        sum.resize(n+1,0);
        myTree.newSegmentTree(n);

    }
    void dfs(int u)
    {
        child[u]=1;
        for(int v:Edge[u]) if(v!=pa[u])
        {
            pa[v]=u;
            sum[v]=sum[u]+weight[v];
            dfs(v);
            child[u]+=child[v];
        }
    }
    void heavy_light(int u){
        if(head[cnt_chain]==0) head[cnt_chain]=u;
        chain[u]=cnt_chain;
        pos[u]=++size;
        
        int min_subtree=-1;
        for(int v:Edge[u]) if(v!=pa[u]){
            if(min_subtree == -1 || child[min_subtree] > child[v]){
                min_subtree=v;
            }
        }
        
        if(min_subtree!=-1) heavy_light(min_subtree);
        
        for(int v:Edge[u]) if(v!=pa[u] && v!=min_subtree){
            cnt_chain++;
            heavy_light(v);
        }
        end[u]=size;
    }
    
    void build(){
        for(int i=1;i<=n;i++) {
            cin>>weight[i];
        }
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            Edge[u].pb(v);
            Edge[v].pb(u);
        }
        sum[1]=weight[1];
        pa[1]=1;
        dfs(1);
        heavy_light(1);
        for(int i=1;i<=n;i++){
            myTree.up(1, 1, n, pos[i], pos[i], sum[i]);
            //cout<<myTree.get(1, 1, n, pos[i])<<' ';
        }
        //cout<<'\n';
        
    }
    void up(int u,ll val){
        myTree.up(1, 1, n, pos[u], end[u], val-weight[u]);
        weight[u]=val;
    }
    ll get(int u){
        return myTree.get(1, 1, n, pos[u]);
    }
};
