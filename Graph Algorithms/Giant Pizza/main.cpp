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
// 0 1, 2, 3 {a , nota}
int nota(int x)
{
    if (EVEN(x))
    {
        return (x + 1);
    }
    return x - 1;
}
class SCC
{
    int n;
    vector<vector<int>> g;
    vector<vector<int>> gr;
    vector<vector<int>> compo;
    vector<int> compnum;
    vector<int> order;
    bool done;

public:
    SCC(int n)
    {
        this->n = n;
        this->g = vector<vector<int>>(this->n);
        this->gr = vector<vector<int>>(this->n);
        this->done = false;
        this->compnum.resize(n);
    }
    void addedge(int a, int b)
    {
        this->g[a].push_back(b);
        this->gr[b].push_back(a);
    }
    void run()
    {
        topologicalsort();
        findscc();
        this->done = true;
    }
    void topologicalsort()
    {
        vector<bool> vis(n, false);
        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
            {
                dfs1(i, vis);
            }
        }
    }
    void dfs1(int i, vector<bool> &vis)
    {
        vis[i] = true;
        for (auto to : this->g[i])
        {
            if (!vis[to])
            {
                dfs1(to, vis);
            }
        }
        order.push_back(i);
    }
    void findscc()
    {
        vector<bool> vis(n, false);
        int sccnum = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (!vis[order[i]])
            {
                this->compo.push_back(vector<int>());
                dfs2(order[i], vis, sccnum++);
            }
        }
    }
    int getid(int x)
    {
        return this->compnum[x];
    }
    void dfs2(int i, vector<bool> &vis, int sccnum)
    {
        this->compo.back().push_back(i);
        vis[i] = true;
        this->compnum[i] = sccnum;
        for (auto to : gr[i])
        {
            if (!vis[to])
            {
                dfs2(to, vis, sccnum);
            }
        }
    }
    vector<int> topologicalorder()
    {
        // only coorrect
        //if the there is not scc of size 2 or more
        assert(done == true);
        auto t = this->order;
        reverse(t.begin(), t.end());
        return t;
    }
    vector<vector<int>> component()
    {
        assert(done == true);
        return this->compo;
    }
};
void solve()
{
    int n, m;
    R(n, m);
    SCC scc(2 * m);
    for (int i = 0; i < n; i++)
    {
        char ch1, ch2;
        int a, b;
        R(ch1, a, ch2, b);
        a--;
        b--;
        a *= 2;
        b *= 2;
        if (ch1 == '-')
            a = nota(a);
        if (ch2 == '-')
            b = nota(b);
        scc.addedge(nota(a), b);
        scc.addedge(nota(b), a);
    }
    scc.run();
    for (int i = 0; i < 2 * m; i += 2)
    {
        if (scc.getid(i) == scc.getid(i + 1))
        {
            W("IMPOSSIBLE");
            return;
        }
    }
    VB assinment(m, false);
    for (int i = 0; i < 2 * m; i += 2)
    {
        if (scc.getid(i) < scc.getid(i + 1))
        {
            assinment[i / 2] = false;
        }
        else
        {
            assinment[i / 2] = true;
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (assinment[i])
        {
            cout << "+ ";
        }
        else
        {
            cout << "- ";
        }
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