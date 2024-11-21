ll pw(ll x, ll n) //nomar pow
{
    ll res = 1;
    for (; n > 0; n >>= 1)
    {
        if (n & 1)
        {
            if (res <= ooo / x)
                res *= x;
            else
                res = +ooo;
        }

        if (x <= ooo / x)
            x *= x;
        else
            x = +ooo;
    }

    return res;
}
ll log(ll q,ll n){  // LOG(q,n)
    ll p = pow(n, double(1.0) / q);
    while (pw(p, q) < n) ++p;
    while (pw(p, q) > n) --p;
    return p;
}
ull mulmod(ull a,ull b,ull mod) //  a * b % mod
{
    ull base=a;
    ull ans=0;
    for (; b > 0; b >>= 1, (base*=2)%=mod)
       if (b & 1) (ans += base) %= mod ;
    
   return ans;
}
ull powmod(ull b, ull e, ull mod) { // a ^ b % mod
    ull ans = 1;
    for (; e ; e >>= 1, b = mulmod(b, b, mod))
        if (e & 1) ans = mulmod (ans, b, mod) ;
    return ans;
}

class Factorial{
    const long long MOD998 = 998244353;
    vector<long> fac = {1,295201906, 160030060, 957629942, 545208507, 213689172, 760025067, 939830261, 506268060, 39806322, 808258749, 440133909, 686156489, 741797144, 390377694, 12629586, 544711799, 104121967, 495867250, 421290700, 117153405, 57084755, 202713771, 675932866, 79781699, 956276337, 652678397, 35212756, 655645460, 468129309, 761699708, 533047427, 287671032, 206068022, 50865043, 144980423, 111276893, 259415897, 444094191, 593907889, 573994984, 892454686, 566073550, 128761001, 888483202, 251718753, 548033568, 428105027, 742756734, 546182474, 62402409, 102052166, 826426395, 159186619, 926316039, 176055335, 51568171, 414163604, 604947226, 681666415, 511621808, 924112080, 265769800, 955559118, 763148293, 472709375, 19536133, 860830935, 290471030, 851685235, 242726978, 169855231, 612759169, 599797734, 961628039, 953297493, 62806842, 37844313, 909741023, 689361523, 887890124, 380694152, 669317759, 367270918, 806951470, 843736533, 377403437, 945260111, 786127243, 80918046, 875880304, 364983542, 623250998, 598764068, 804930040, 24257676, 214821357, 791011898, 954947696, 183092975};
public:
    ll factorial(ll n){
        if(n>=MOD998) return 0;
        ll val=fac[n/10000000];
        for(ll i=10000000*(n/10000000)+1;i<=n;i++){
            val*=i;
            val%=MOD998;
        }
        return val;
    }
};

const int N=2e5;
ll gt[N+5],igt[N+5];

ll ckn(int n,int k){
    assert(n >= k);
    return gt[n]*igt[k]%mod*igt[n-k]%mod;
}

gt[0]=1;
for(int i=1;i<=N;i++) gt[i]=(gt[i-1]*i)%mod;
igt[N]=powmod(gt[N], mod-2, mod);
for(int i=N-1;i>=0;i--) igt[i]=(igt[i+1]*(i+1))%mod;
    


const int N=1e7;
int minP[N+5];
void sang(){
    for(int i=0;i<=N;i++) minP[i]=i;
    for(int i=2;i*i<=N;i++) if(minP[i]==i){
        for(int j=i*i;j<=N;j+=i) if(minP[j]==j)
            minP[j]=i;
    }
}
bool isPrime(ll n)
{
    if (n < 2 || n == 4) return false;
    if (n == 2 || n == 3 || n == 5) return true;
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) return false;

    for (int x = 5; 1LL * x * x <= n; x += 6)
        if (n % x == 0 || n % (x + 2) == 0)
            return false;
            
    return true;
}
bool MillerRabin (ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    ull s = __builtin_ctzll(n-1);
    ull d = n >> s;
    for (ull a : A) { // ^
        ull p = powmod(a%n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = mulmod(p, p, n);
        if (p != n-1 && i != s) return 0;
    }
    return 1;
}
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n != 1) {
        res -= res / n;
    }
    return res;
}
int phi[5000001];
void EulerPhi(int N)
{
    for(ull i=0;i<=N;i++) phi[i]=i;
    for(ull i=2;i<=N;i++)
        if(phi[i]==i)
            for(ull j=i;j<=N;j+=i)
                phi[j]-=phi[j]/i;
}
struct Matrix{
    int x,y;
    vt<vt<int>> a;
    Matrix(int _x,int _y)
    {
        x=(int)_x;
        y=(int)_y;
        a.resize(x,vt<int>(y,0));
    }
    Matrix Identity_Matrix(int n)
    {
        Matrix I = Matrix(n, n);
        while (n--) I.a[n][n] = 1;
        return I;
    }
    Matrix operator *(const Matrix& other) { //[x,y] * [y,z] = [x,z]
        // Check if can multiply
        assert(y == other.x);
        int z= other.y;
        Matrix product(x,z);
        for(int i = 0; i <x; ++i) {
            for(int j = 0; j < z; ++j) {
                for(int k = 0; k < y; ++k) {
                    (product.a[i][j] += 1LL * a[i][k] * other.a[k][j] % mod ) %= mod;
                }
            }
        }
        return product;
    }
    void operator *=(const Matrix& other) { //[x,y] * [y,z] = [x,z]
        // Check if can multiply
        assert(y == other.x);
        int z= other.y;
        Matrix product(x,z);
        for(int i = 0; i <x; ++i) {
            for(int j = 0; j < z; ++j) {
                for(int k = 0; k < y; ++k) {
                    (product.a[i][j] += 1LL * a[i][k] * other.a[k][j] % mod ) %= mod;
                }
            }
        }
        *this = product;
    }
    Matrix operator ^(long long M) {
        // Check square matrix
        assert(x == y);

        Matrix base = (*this);
        Matrix ans  = Identity_Matrix(x);
        for (; M > 0; M >>= 1, base = base * base)
            if (M & 1) ans = ans * base;
        return ans;
    }
    void operator ^=(long long M) {
        // Check square matrix
        assert(x == y);

        Matrix base = (*this);
        Matrix ans  = Identity_Matrix(x);
        for (; M > 0; M >>= 1, base = base * base)
            if (M & 1) ans = ans * base;
        *this = ans;
    }
};
struct RealMatrix{
    int x,y;
    vt<vt<double>> a;
    RealMatrix(int _x,int _y)
    {
        x=(int)_x;
        y=(int)_y;
        a.resize(x,vt<double>(y,0));
    }
    RealMatrix Identity_RealMatrix(int n)
    {
        RealMatrix I = RealMatrix(n, n);
        while (n--) I.a[n][n] = 1;
        return I;
    }
    RealMatrix operator *(const RealMatrix& other) { //[x,y] * [y,z] = [x,z]
        // Check if can multiply
        assert(y == other.x);
        int z= other.y;
        RealMatrix product(x,z);
        for(int i = 0; i <x; ++i) {
            for(int j = 0; j < z; ++j) {
                for(int k = 0; k < y; ++k) {
                    product.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return product;
    }
    void operator *=(const RealMatrix& other) { //[x,y] * [y,z] = [x,z]
        // Check if can multiply
        assert(y == other.x);
        int z= other.y;
        RealMatrix product(x,z);
        for(int i = 0; i <x; ++i) {
            for(int j = 0; j < z; ++j) {
                for(int k = 0; k < y; ++k) {
                    product.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        *this = product;
    }
    RealMatrix operator ^(long long M) {
        // Check square matrix
        assert(x == y);

        RealMatrix base = (*this);
        RealMatrix ans  = Identity_RealMatrix(x);
        for (; M > 0; M >>= 1, base = base * base)
            if (M & 1) ans = ans * base;
        return ans;
    }
    void operator ^=(long long M) {
        // Check square matrix
        assert(x == y);

        RealMatrix base = (*this);
        RealMatrix ans  = Identity_RealMatrix(x);
        for (; M > 0; M >>= 1, base = base * base)
            if (M & 1) ans = ans * base;
        *this = ans;
    }
};

