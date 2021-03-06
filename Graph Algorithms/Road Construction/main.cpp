#include <iostream>
#include <bitset>
#include <map>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <set>
#include <utility>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cassert>
#include <chrono>
#include <cctype>
#include <iomanip>
#include <stack>
#include <ctime>
#include <iterator>
#include <sstream>
using namespace std;
#define sync                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define REPR(i, a, b) for (int i = (a); i > (b); i--)
#define ALL(x) (x).begin(), (x).end()
#define SETALL(x, val) fill(ALL(x), val)
#define SORT_UNIQUE(c) (sort(c.begin(), c.end()), c.resize(distance(c.begin(), unique(c.begin(), c.end()))))
#define SORT(a) (sort(ALL(a)))
#define SORTR(a) (SORT(a), reverse(ALL(a)))
#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))
#define ODD(x) (x & 1)
#define EVEN(x) (!(x & 1))
#define MEMS0(x) memset((x), 0, sizeof(x))
#define MEMS1(x) memset((x), 1, sizeof(x))
#define MEMSM1(x) memset((x), -1, sizeof(x))
#define PB emplace_back
#define MP make_pair
#define F first
#define S second
#define VB vector<bool>
#define VVB vector<VB>
#define VI vector<int>
#define VVI vector<VI>
#define PII pair<int, int>
#define VPII vector<PII>
#define SP(x) setprecision(x)
#define endl '\n'
#define LL long long
#define LD long double
#define SZ(z) (int)(z).size()
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define EPS 0.0000001 // eps = 1e-7
#define PI 3.141592653589793238
const LL MOD = 1000000007;
#ifndef ONLINE_JUDGE
#define DEBUG(...)      \
    cout << "[DEBUG] "; \
    W(__VA_ARGS__);
#else
#define DEBUG(...)
#endif
template <class T>
void _R(T &x)
{
    cin >> x;
}
void _R(int &x) { cin >> x; }
void _R(int64_t &x) { cin >> x; }
void _R(double &x) { cin >> x; }
void _R(long double &x) { cin >> x; }
void _R(char &x) { cin >> x; }
void _R(char *x) { cin >> x; }
void _R(string &x) { cin >> x; }
void R() {}
template <class T, class... U>
void R(T &head, U &... tail)
{
    _R(head);
    R(tail...);
}
template <class T>
void _W(const T &x) { cout << x; }
void _W(const int &x) { cout << x; }
void _W(const int64_t &x) { cout << x; }
void _W(const double &x) { cout << fixed << SP(8) << x; }
void _W(const long double &x) { cout << fixed << SP(16) << x; }
void _W(const char &x) { cout << x; }
void _W(const char *x) { cout << x; }
void _W(const string &x) { cout << x; }
template <class T, class U>
void _W(const pair<T, U> &x)
{
    _W(x.F);
    cout << ' ';
    _W(x.S);
}
template <class T>
void _W(const vector<T> &x)
{
    for (auto i = x.begin(); i != x.end(); _W(*i++))
        if (i != x.cbegin())
            cout << ' ';
}
void W() {}
template <class T, class... U>
void W(const T &head, const U &... tail)
{
    _W(head);
    cout << (sizeof...(tail) ? ' ' : '\n');
    W(tail...);
}

class DSU
{
    vector<int> par1d;
    vector<int> sz1d;
    vector<vector<pair<int, int>>> par2d;
    vector<vector<int>> sz2d;
    int D1, D2;
    int best, numebers;

public:
    DSU(int n)
    {
        par1d = vector<int>(n);
        sz1d = vector<int>(n);
        REP(i, 0, n)
        {
            sz1d[i] = 1;
            par1d[i] = i;
        }
        D1 = 1, D2 = 0;
        best = 1;
        numebers = n;
    }
    DSU(int n, int m)
    {
        par2d = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(m));
        sz2d = vector<vector<int>>(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                par2d[i][j] = MP(i, j);
                sz2d[i][j] = 1;
            }
        }
        D1 = 0, D2 = 1;
    }
    pair<int, int> findparent(pair<int, int> a)
    {
        if (par2d[a.first][a.second] == a)
            return a;
        return par2d[a.first][a.second] = findparent(par2d[a.first][a.second]);
    }
    int findparent(int a)
    {
        if (par1d[a] == a)
            return a;
        return par1d[a] = findparent(par1d[a]);
    }
    bool unite(pair<int, int> a, pair<int, int> b)
    {
        a = findparent(a);
        b = findparent(b);
        if (a == b)
        {
            return false; // unsucess
        }
        if (sz2d[a.first][a.second] < sz2d[b.first][b.second])
        {
            swap(a, b);
        }
        par2d[b.first][b.second] = a;
        sz2d[a.first][a.second] += sz2d[b.first][b.second];
        return true; // sucess;
    }
    bool unite(int a, int b)
    {
        a = findparent(a);
        b = findparent(b);
        if (a == b)
        {
            return false;
        }
        if (sz1d[a] < sz1d[b])
        {
            swap(a, b);
        }
        par1d[b] = a;
        sz1d[a] += sz1d[b];
        best = max(best, sz1d[a]);
        numebers--;
        return true;
    }
    pair<int, int> getans()
    {
        return MP(numebers, best);
    }
    bool isroot(pair<int, int> a)
    {
        return findparent(a) == a;
    }
    bool isroot(int a)
    {
        return findparent(a) == a;
    }
    int size(pair<int, int> a)
    {
        a = findparent(a);
        return sz2d[a.first][a.second];
    }
    int size(int a)
    {
        a = findparent(a);
        return sz1d[a];
    }
};
void solve()
{
    int n, m;
    R(n, m);
    DSU dsu(n);
    REP(i, 0, m)
    {
        int a, b;
        R(a, b);
        dsu.unite(a - 1, b - 1);
        W(dsu.getans());
    }
}

signed main()
{
    sync;
#ifndef ONLINE_JUDGE
    auto begin = std::chrono::high_resolution_clock::now();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    //cin >> t;
    for (int testcase = 1; testcase <= t; testcase++)
    {
        //cout << "Case #" << testcase << ": ";
        solve();
    }

#ifndef ONLINE_JUDGE
    auto end = std::chrono::high_resolution_clock::now();
    cerr << setprecision(4) << fixed;
    cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " seconds" << endl;
#endif
    return 0;
}