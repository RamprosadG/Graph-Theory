#include<bits/stdc++.h>
using namespace std;

#define ll       long long
#define ull      unsigned ll
#define pii      pair<int, int>
#define pll      pair<ll, ll>
#define mp       make_pair
#define ff       first
#define ss       second
#define sz(x)    (int) x.size()
#define all(v)   v.begin(), v.end()

template <typename T> inline void smin(T &a, T b) {a = a < b ? a : b;}
template <typename T> inline void smax(T &a, T b) {a = a > b ? a : b;}

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl;}
template<typename T, typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << ", ";
	err(++it, args...);
}

template <typename T> inline void Int(T &n) {
	n = 0; int f = 1; register int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) n = (n << 3) + (n << 1) + ch - '0';
	n = n * f;
}

template <typename T, typename TT> inline void Int(T &n, TT &m) { Int(n); Int(m); }
template <typename T, typename TT, typename TTT> inline void Int(T &n, TT &m, TTT &l) { Int(n, m); Int(l); }

const int mod = (int) 1e9 + 7;

inline int add(int a, int b) {a += b; return a >= mod ? a - mod : a;}
inline int sub(int a, int b) {a -= b; return a < 0 ? a + mod : a;}
inline int mul(int a, int b) {return (ll) a * b % mod;}

const int inf = (int) 2e9 + 5;
const ll  Inf = (ll) 2e18 + 5;
const int N   = (int) 2e5 + 5;

vector<int> g[N];
int col[N], cnt[N], sz[N], ans[N];
bool big[N];
vector<pii> query[N];

void getsz(int u, int p = -1) {
	sz[u] = 1;
	for (auto v : g[u]) {
		if (v != p) getsz(v, u), sz[u] += sz[v];
	}
}

void add(int u, int p, int x) {
	cnt[col[u]] += x;
	for (auto v : g[u]) {
		if (v != p and !big[v]) add(v, u, x);
	}
}

void dfs(int u, int p, bool keep) {
	int mx = -1, bigchild = -1;
	for (auto v : g[u]) {
		if (v != p and sz[v] > mx) mx = sz[v], bigchild = v;
	}
	for (auto v : g[u]) {
		if (v != p and v != bigchild) dfs(v, u, false);
	}
	if (bigchild != -1) dfs(bigchild, u, true), big[bigchild] = true;
	add(u, p, 1);
	for (auto x : query[u]) {
		ans[x.ff] = cnt[x.ss];
	}
	if (bigchild != -1) big[bigchild] = false;
	if (!keep) add(u, p, -1);
}

int solve() {
	int n; Int(n);
	for (int i = 1; i <= n; i++) {
		Int(col[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v; Int(u, v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int q; Int(q);
	for (int i = 1; i <= q; i++) {
		int u, c; Int(u, c);
		query[u].push_back({i, c});
	}
	getsz(1);
	dfs(1, -1, false);
	for (int i = 1; i <= q; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

int main() {
	//ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int test = 1, tc = 0;
	//Int(test);
	//cin >> test;
	while (test--) {
		//printf("Case %d: ", ++tc);
		solve();
	}
	return 0;
}
