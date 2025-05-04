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
#define BUG(x)    cerr << #x << " = " << x << '\n';
#define FPTU      ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int mod = 1e9+7; //MODDDDDDDDDDDDD

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
// =========> <3 VietHai1709 <3  <=======
const int N = 1e5 + 5;
string s;
ll base = 97;
ll poww[N];

unordered_map<string, bool> short_str;
vt<pii> long_str;

int W;

void solve() {
    cin >> s;
    W = sqrt((int)s.size());
    
    int m;
    cin >> m;
    
    int maxShort = 0;
    while (m--) {
        string t;
        cin >> t;
        int h = 0;
        for (char c : t) {
            h = (1ll * h * base + c - 'a' + 1) % mod;
        }

        if ((int)t.size() <= W) {
            short_str[t] = true;
            maxShort = max(maxShort, (int)t.size());
        } else {
            long_str.pb({(int)t.size(), h});
        }
    }

    sort(all(long_str));
    reverse(all(long_str));

    poww[0] = 1;
    for (int i = 1; i < N; i++) {
        poww[i] = poww[i - 1] * base % mod;
    }

    string R = "";
    vt<ll> hashR(1, 0);

    for (char c : s) {
        R += c;
        ll newHash = (hashR.back() * base + c - 'a' + 1) % mod;
        hashR.pb(newHash);

        bool erased = true;
        while (erased) {
            erased = false;

            // Check long strings
            for (pii &PII : long_str) {
                int len = PII.first;
                int h   = PII.second;
                if ((int)R.size() >= len) {
                    int i = (int)R.size() - len + 1;
                    
                    ll suffix_hash = (hashR.back() - (hashR[i - 1] * poww[len]) % mod + mod) % mod;

                    if (suffix_hash == h) {
                        R.resize(R.size() - len);
                        hashR.resize(hashR.size() - len);
                        erased = true;
                        break;
                    }
                }
            }

            if (erased) continue;

            // Check short strings
            int maxCheck = min(maxShort, (int)R.size());
            for (int len = maxCheck; len >= 1; --len) {
                string suffix = R.substr(R.size() - len, len);
                if (short_str.count(suffix)) {
                    R.resize(R.size() - len);
                    hashR.resize(hashR.size() - len);
                    erased = true;
                    break;
                }
            }
        }
    }

    cout << R;
}
int main()
{
    
    FPTU;
    freopen("sample.inp", "r", stdin);
    freopen("sample.out", "w", stdout);
    
//    freopen("censor.in", "r", stdin);
//    freopen("censor.out", "w", stdout);

    int t=1;
//    cin>>t;
    while(t--){
        solve();
    }
    cerr << "\nTime elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s.\n";

    return 0;
}
    
