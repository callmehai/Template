struct line{
    ll a,b;
    line(ll x=0,ll y=ooo)
    {
        a=x; b=y;
    }
    ll get(ll x)
    {
        return a*x+b;
    }
};
struct ConvextHullTrick{
    int n;
    int flag;
    vt<line> Line;
    ConvextHullTrick(){
        n=0;
        flag=0;
        Line.clear();
    }
    bool bad(line u,line v,line w)
    {
        return (double)(u.b-w.b)/(w.a-u.a)<=(double)(u.b-v.b)/(v.a-u.a);
        //return (u.b-w.b)*(v.m-u.m)<=(u.b-v.b)*(w.m-u.m);
    }
    void add(line L)
    {
        while(n>=2 && bad(Line[n-2],Line[n-1],L))
        {
            Line.pop_back();
            n--;
        }
        Line.pb(L);
        n++;
    }
    ll query(ll x)
    {
        if(flag>n-1) flag=n-1;
        while(flag+1<n && Line[flag].get(x)>Line[flag+1].get(x)) flag++;
        return Line[flag].get(x);
    }
};

struct node{
    int tag;
    line L;
};
struct LichaoTree{
    // get max => lower convexhull
    // get min => upper convexhull

    vt<node> F;
    int n;
    LichaoTree(int _){
        n=_;
        F.resize(n<<2);
    }
    void reset(){
        F.clear();
        F.resize(n<<2);
    }
    void down(int p) {
        if(F[p].tag) {
            F[p*2]={1,{0,ooo}};
            F[p*2+1]={1,{0,ooo}};
            F[p].tag=0;
        }
    }
    void add(int id,int l,int r,line cur)
    {
        int mid=(l+r)>>1;
        bool lef = cur.get(l) < F[id].L.get(l);
        bool mi = cur.get(mid) < F[id].L.get(mid);
        if(mi) swap(F[id].L,cur);
        if(l==r) return;
        down(id);
        if(lef==mi) add(id*2+1,mid+1,r,cur);
        else add(id*2,l,mid,cur);
    }

    ll query(int id,int l,int r,ll x)
    {
        int mid=(l+r)>>1;
        if(l==r) return F[id].L.get(x);
        down(id);
        ll ans=F[id].L.get(x);
        if(x<=mid) minimize(ans, query(id*2,l,mid,x));
        else minimize(ans, query(id*2+1,mid+1,r,x));
        return ans;
    }
    
};
