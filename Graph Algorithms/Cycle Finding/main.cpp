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
#define int long long
template <typename T = int64_t>
class BellmanFord
{
    int n;
    vector<T> dist;
    vector<pair<pair<int, int>, T>> edges;
    vector<int> par;
    vector<int> sources;
    vector<int> anycycle;
    bool done;
    bool contains_negative_weight_cyc;
    T oo;

public:
    BellmanFord(int n)
    {
        oo = 0x3f3f3f3f3f3f3f3f;
        this->n = n;
        done = false;
        contains_negative_weight_cyc = false;
        dist.resize(this->n);
        par.resize(this->n);
    }
    void addedge(int a, int b, T cost, bool bidir = false)
    {
        edges.push_back(MP(MP(a, b), cost));
        if (bidir)
        {
            edges.push_back(MP(MP(b, a), cost));
        }
    }
    void run(vector<int> sources)
    {
        for (int i = 0; i < n; i++)
        {
            dist[i] = oo;
            par[i] = -1;
        }
        for (auto s : sources)
        {
            dist[s] = 0;
        }
        int a, b, last_update;
        T cos_e;
        for (int i = 0; i < n; i++) // n-1 steps at most
        {
            bool anyrelax = false;
            last_update = -1;
            for (auto pt : edges)
            {
                a = pt.first.first;
                b = pt.first.second;
                cos_e = pt.second;
                if (dist[a] < oo && dist[b] > dist[a] + cos_e)
                {
                    dist[b] = dist[a] + cos_e;
                    par[b] = a;
                    last_update = b;
                    anyrelax = true;
                }
            }
            if (!anyrelax)
                break;
        }
        if (last_update != -1)
        {
            contains_negative_weight_cyc = true;
            for (int i = 0; i < n; i++)
            {
                last_update = par[last_update];
            }
            anycycle.push_back(last_update);
            for (int u = par[last_update]; u != last_update; u = par[u])
            {
                anycycle.push_back(u);
            }
            reverse(anycycle.begin(), anycycle.end());
        }
        this->sources = sources;
        done = true;
    }
    vector<int> negativecycle()
    {
        return anycycle;
    }
    bool negative_weight_cycle()
    {
        return contains_negative_weight_cyc;
    }
    T getdist(int to)
    {
        return dist[to];
    }
};
void solve()
{
    int n, m;
    R(n, m);
    vector<pair<PII, int>> edges;

    BellmanFord<long long> bf(n);
    REP(i, 0, m)
    {
        int a, b, c;
        R(a, b, c);
        edges.push_back(MP(MP(a - 1, b - 1), c));
        bf.addedge(a - 1, b - 1, c);
    }
    vector<int> sources;
    REP(i, 0, n)
    {
        sources.PB(i);
    }
    bf.run(sources);
    if (bf.negative_weight_cycle())
    {
        W("YES");
        VI path = bf.negativecycle();
        path.push_back(path[0]);
        for (auto x : path)
        {
            cout << x + 1 << ' ';
        }
    }
    else
    {

        W("NO");
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