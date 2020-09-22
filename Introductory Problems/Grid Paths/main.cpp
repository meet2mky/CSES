/*****************************************************************
IN GOD WE TRUST !!   

Author:- meet2mky
Date: -
Problem:-
Institue:- NITA
******************************************************************/
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
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define repinv(i, a, b) for (int i = (a); i > (b); i--)
#define all(x) (x).begin(), (x).end()
#define setall(x, val) fill(all(x), val)
#define odd(x) (x & 1)
#define even(x) (!(x & 1))
#define pb push_back
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define sp(x) setprecision(x)
#define endl '\n'
#define ll long long
#define ld long double
#define SZ(z) (int)(z).size()
#define inf 0x3f3f3f3f
#define linf 0x3f3f3f3f3f3f3f3f
#define eps 0.0000001 // eps = 1e-7
#define PI 3.141592653589793238

//#define int long long
const int MOD = 1000000007;

//variadic functions
template <typename T>
T sum() { return 0; }
template <typename T, typename... Args>
T sum(T a, Args... args) { return a + sum(args...); }

//Debugger  -------------------------------------------->
#define error(args...)                           \
    {                                            \
        string _s = #args;                       \
        replace(_s.begin(), _s.end(), ',', ' '); \
        stringstream _ss(_s);                    \
        istream_iterator<string> _it(_ss);       \
        err(_it, args);                          \
    }

void err(istream_iterator<string> it)
{
}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}
//Debugger  <--------------------------------------------
/*****************************************************************
Read the problem carefully!!
Take inputs carefully
Care for array index out of bound errors
Check for overflow
Divide the problem in several parts if possible
Keep Calm and believe on yourself.
Do not panic & work hard you will get it right one day


LOOP ITERATORS MIXING ~ WASTE OF TIME AND LOTS OF BUG
******************************************************************/
//  cnt(R) - cnt(L) <= 7 and cnt(L)-cnt(R) >= 0;
// cnt(D) - cnt(U) <= 7 and cnt(U)-cnt(D) >= 0;
// backtrack
string pathoption;
bool vis[7][7];
int ans = 0;
int tmp;
vi dx = {1, -1, 0, 0};
vi dy = {0, 0, -1, 1};
char dir[] = {'R', 'L', 'U', 'D'};
map<char, int> rdir = {{'R', 0}, {'L', 1}, {'U', 2}, {'D', 3}};
bool reachable(int row, int col, int used)
{
    int can = 48 - used;
    int need = abs(row - 6) + abs(col - 0);
    return can >= need;
}
void solve(int row, int col, int used)
{
    if (used == 48)
    {
        if (row == 6 && col == 0)
        {
            cout << pathoption << endl;
            ans++;
            cout << ans << endl;
        }
        return;
    }
    if (!reachable(row, col, used))
        return;
    if (pathoption[used] != '?')
    {
        // restricted path
        int i = rdir[pathoption[used]];
        int nrow = row + dy[i];
        int ncol = col + dx[i];
        if (nrow <= 6 && nrow >= 0 && ncol >= 0 && ncol <= 6 && !vis[nrow][ncol])
        {
            vis[nrow][ncol] = true;
            solve(nrow, ncol, used + 1);
            vis[nrow][ncol] = false;
        }
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int nrow = row + dy[i];
        int ncol = col + dx[i];
        if (nrow <= 6 && nrow >= 0 && ncol >= 0 && ncol <= 6 && !vis[nrow][ncol])
        {
            vis[nrow][ncol] = true;
            pathoption[used] = dir[i];
            solve(nrow, ncol, used + 1);
            pathoption[used] = '?';
            vis[nrow][ncol] = false;
        }
    }
}
void solve()
{
    cin >> pathoption;
    memset(vis, false, sizeof vis);
    solve(0, 0, 0);
    cout << ans << endl;
}
signed main()
{
    sync;
#ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    for (int testcase = 1; testcase <= t; testcase++)
    {
#ifndef ONLINE_JUDGE
        error(testcase);
#endif
        solve();
    }
    return 0;
}