//#pragma GCC optimize ("O3")

#include <bits/stdc++.h>

using namespace std;
 
// ************ Define ************
#define ll  long long
#define ull unsigned long long
#define usi unsigned int
#define pii pair<int,int>
#define pll pair<ll,ll>
#define plp pair<ll,pll>
#define ppl pair<pll,ll>
#define ppp pair<pii,pii>
#define oo  1000111000
#define ooo 1000111000111000111
#define inf 0x3f
#define INF 4557430888798830399
#define fi  first
#define se  second
#define vt  vector
#define pb  push_back
#define el  cout<<'\n';

#define all(arr)  arr.begin(),arr.end()
#define bit(n, i) (((n) >> (i)) & 1)
#define TIME      (1.0 * clock() / CLOCKS_PER_SEC)
#define BUG(x)    cerr << #x << " = " << x << '\n';
#define FPTU      ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

ll mod = 1e9+7; //MODDDDDDDDDDDDD

template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y; return true;
    } else return false;
}

template<class X, class Y>
bool minimize(X &x, const Y &y) {
    if (x > y) {
        x = y; return true;
    } else return false;
}

template<class X, class Y>
void add(X &a, const Y b) {
    a+=b;
    if(a>=mod) a-=mod;
}

template<class X, class Y>
void sub(X &a, const Y b) {
    a-=b;
    if(a<0) a+=mod;
}
void read_file()
{
    freopen("sample.inp","r",stdin);
    freopen("sample.out","w",stdout);
}
// =========> <3 VietHai1709 <3  <=======
vector<int> col;
int zero,one,two;
int N,M,K;
struct node{
    int n,zero,one,two,k;
};

map<node,int> dp;

int dq(int n,int k){
    if(n==0){
        return k==0;
    }
    
    node cur;
    cur={n,zero,one,two,k};
    
//    if(dp[{n,zero,one,two,k}]!=0){
//        if(dp[{n,zero,one,two,k}]==-1) return 0;
//        return dp[{n,zero,one,two,k}];
//    }
    int ans=0;
    
    // no rook
    add(ans,dq(n-1,k));

    // 1 rook
    if(k>=1){
        if(zero>0){
            zero--;
            one++;
            
            int sub = dq(n-1,k-1);
            
            zero++;
            one--;
            
            (sub*=zero)%=mod;
            add(ans,sub);
        }
        
        if(one>0){
            one--;
            two++;
            
            int sub = dq(n-1,k-1);
            
            one++;
            two--;
            
            (sub*=one)%=mod;
            add(ans,sub);
        }
    }

    
    // 2 rooks
    if(k>=2)
    {
        if(zero>1){
            zero-=2;
            two+=2;
            
            int sub=dq(n-1,k-2);
            
            zero+=2;
            two-=2;
            
            (sub*=zero*(zero-1)/2 )%=mod;
            
            add(ans,sub);
        }
    }
    
    if(ans==0) dp[cur]=-1;
    else  dp[cur]=ans;
    
    return ans;
}
void solve(){
    cin>>N>>M>>K;
    mod=1000001;
    
//    memset(dp,0,sizeof(dp));
    col.resize(M+1,0);
    zero=M;
    one = two = 0;
    
    cout<<dq(N,K); el;
}

int main()
{
    
    FPTU;
    read_file();

    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    cerr << "\nTime elapsed: " << TIME << " s.\n";
    return 0;
}
