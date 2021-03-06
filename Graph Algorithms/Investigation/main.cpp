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
template <class T = int64_t>
class Dijkstra
{
public:
    int n, source;                  // number of nodes,source
    bool done;                      // dijkstra [done] by source
    vector<vector<pair<int, T>>> g; // graph directed
    vector<bool> vis;               // if reachable x upon calling run(x)
    vector<int> par;                // parent array for run(x)
    vector<T> dist;                 // dist array for run(x)

    //----------------------------------------------------------------//
    T oo = 0x3f3f3f3f3f3f3f3f; // SET THIS PLEASE FIRST
    //----------------------------------------------------------------//
    /* 
        ZERO based indexing /// BE CAREFUL.....
        assumes NO negative weight cycle......
    */
    Dijkstra(int n_)
    {
        this->n = n_;
        g.resize(this->n);
        vis.resize(this->n);
        par.resize(this->n);
        dist.resize(this->n);
        source = -1;
        done = false;
    }
    void addedge(int a, int b, T cost, bool bidir = false)
    {
        this->g[a].push_back(make_pair(b, cost));
        if (bidir)
        {
            this->g[b].push_back(make_pair(a, cost));
        }
    }
    void run(int s)
    {
        for (int i = 0; i < this->n; i++)
        {
            this->dist[i] = oo;
            this->vis[i] = false;
            this->par[i] = false;
        }
        this->dist[s] = 0; // refrence distance
        this->par[s] = -1;
        auto comp = [](const pair<int, T> &a, const pair<int, T> &b) {
            return a.second > b.second;
        };
        priority_queue<pair<int, T>, vector<pair<int, T>>, decltype(comp)> pq(comp);
        pq.push(make_pair(s, this->dist[s]));

        while (!pq.empty())
        {
            int u = pq.top().first;
            T dis = pq.top().second;
            pq.pop();
            if (this->vis[u])
            {
                continue;
            }
            this->vis[u] = true;
            for (PII nx : g[u])
            {
                if (this->dist[nx.first] > dis + nx.second) // relax
                {
                    this->dist[nx.first] = dis + nx.second;
                    this->par[nx.first] = u;
                    pq.push(make_pair(nx.first, this->dist[nx.first]));
                }
            }
            this->source = s;
            this->done = true;
        }
    }
    vector<T> getdistarray()
    {
        assert(done == true && "RUN FIRST");
        return this->dist;
    }
    vector<bool> getvisarray()
    {
        assert(done == true && "RUN FIRST");
        return this->vis;
    }
    vector<int> getpararray()
    {
        assert(done == true && "RUN FIRST");
        return this->par;
    }
    T getdist(int to)
    {
        assert(done == true && "RUN FIRST");
        return this->dist[to];
    }
    bool reachable(int to)
    {
        assert(done == true && "RUN FIRST");
        return this->vis[to];
    }
    vector<int> getpath(int to)
    {
        if (!reachable(to))
        {
            return vector<int>();
        }

        vector<int> path;
        for (int u = to; u != this->source; u = this->par[u])
        {
            path.push_back(u);
        }
        path.push_back(this->source);
        reverse(path.begin(), path.end());
        return path;
    }
};
int n, m;
const int N = 1e5 + 10;
vector<pair<int, long long>> g[N];
vector<int> color(N);
vector<long long> ways(N);
vector<int> maxe(N);
vector<int> mine(N);
void dfs(int s, int p = -1)
{
    color[s] = 1;
    for (auto next : g[s])
    {
        if (p == next.first)
            continue;
        if (color[next.first] == 0)
        {
            dfs(next.first, s);
        }
        ways[s] = (ways[next.first] + ways[s]) % MOD;
        maxe[s] = max(maxe[s], 1 + maxe[next.first]);
        mine[s] = min(mine[s], 1 + mine[next.first]);
    }
    color[s] = 2;
}
void solve()
{
    R(n, m);
    Dijkstra<long long> D(n), DR(n);
    vector<pair<PII, long long>> edges;
    REP(i, 0, m)
    {
        int a, b;
        long long c;
        R(a, b, c);
        D.addedge(a - 1, b - 1, c);
        DR.addedge(b - 1, a - 1, c);
        edges.push_back({{a, b}, c});
    }
    D.run(0);
    DR.run(n - 1);
    long long best_cost = D.getdist(n - 1);
    for (auto ed : edges)
    {
        int a = ed.first.first;
        int b = ed.first.second;
        long long c = ed.second;
        if (D.getdist(a - 1) + c + DR.getdist(b - 1) == best_cost)
        {
            g[a].push_back({b, c});
        }
    }
    ways[n] = 1;
    SETALL(mine, INF);
    mine[n] = 0;
    dfs(1);
    cout << best_cost << ' ' << ways[1] << ' ' << mine[1] << ' ' << maxe[1] << endl;
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