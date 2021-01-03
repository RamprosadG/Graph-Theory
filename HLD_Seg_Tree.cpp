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
const int M   = (int) 18;


int num = 1;
vector<int> g[N], chain[N];
vector<ll> node[N];
int idx[N], pos[N], sz[N], dep[N], par[M][N];
bool vis[N];
int a[N];

void build(int pos, int left, int right, int c) {
	if (left == right) {
		node[c][pos] = a[chain[c][left - 1]];
		return;
	}
	int mid = (left + right) >> 1;
	build(pos * 2, left, mid, c);
	build(pos * 2 + 1, mid + 1, right, c);
	node[c][pos] = node[c][pos * 2] + node[c][pos * 2 + 1];
}

void update(int pos, int left, int right, int x, int val, int c) {
	if (left > x or right < x) return;
	if (left == right) {
		node[c][pos] += val;
		return;
	}
	int mid = (left + right) >> 1;
	update(pos * 2, left, mid, x, val, c);
	update(pos * 2 + 1, mid + 1, right, x, val, c);
	node[c][pos] = node[c][pos * 2] + node[c][pos * 2 + 1];
}

ll query(int pos, int left, int right, int x, int y, int c) {
	if (left > y or right < x) return 0;
	if (left >= x and right <= y) return node[c][pos];
	int mid = (left + right) >> 1;
	ll m = query(pos * 2, left, mid, x, y, c);
	ll n = query(pos * 2 + 1, mid + 1, right, x, y, c);
	return m + n;
}

void lca_build(int u, int d = 1) {
	vis[u] = true, sz[u] = 1, dep[u] = d;
	for (int i = 1; i < M; i++) {
		par[i][u] = par[i - 1][par[i - 1][u]];
	}
	for (int v : g[u]) {
		if (!vis[v]) {
			par[0][v] = u;
			lca_build(v, dep[u] + 1);
			sz[u] += sz[v];
		}
	}
}

int lca_query(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = M - 1; i >= 0 and u != v; i--) {
		if (dep[par[i][u]] >= dep[v]) u = par[i][u];
	}
	if (u == v) return u;
	for (int i = M - 1; i >= 0; i--) {
		if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
	}
	return par[0][u];
}

void hld_build(int u, int p = -1) {
	chain[num].push_back(u), idx[u] = num;
	pos[u] = sz(chain[num]);
	int mx = -1, bigchild = -1;
	for (int v : g[u]) {
		if (v != p and sz[v] > mx) mx = sz[v], bigchild = v;
	}
	if (bigchild != -1) hld_build(bigchild, u);
	for (int v : g[u]) {
		if (v != p and v != bigchild) num++, hld_build(v, u);
	}
}

void hld_process() {
	for (int i = 1; i <= num; i++) {
		node[i].resize(sz(chain[i]) * 4, 0);
		build(1, 1, sz(chain[i]), i);
	}
}

void update(int u, int val) {
	int x = pos[u], c = idx[u];
	update(1, 1, sz(chain[c]), x, val, c);
}

ll hld_query(int u, int v) {
	int l = lca_query(u, v);
	ll ans = 0;
	while (1) {
		int c = idx[u];
		if (idx[u] == idx[l]) {
			ans += query(1, 1, sz(chain[c]), pos[l], pos[u], c);
			break;
		}
		ans += query(1, 1, sz(chain[c]), 1, pos[u], c);
		u = par[0][chain[c][0]];
	}
	while (1) {
		int c = idx[v];
		if (idx[v] == idx[l]) {
			ans += query(1, 1, sz(chain[c]), pos[l] + 1, pos[v], c);
			break;
		}
		ans += query(1, 1, sz(chain[c]), 1, pos[v], c);
		v = par[0][chain[c][0]];
	}
	return ans;
}

int solve() {
	int n; Int(n);
	for (int i = 1; i <= n; i++) {
		Int(a[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v; Int(u, v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	par[0][1] = 1;
	lca_build(1);
	hld_build(1);
	hld_process();
	int q; Int(q);
	while (q--) {
		int ck; Int(ck);
		if (!ck) {
			int u, val; Int(u, val);
			update(u, val);
		} else {
			int u, v; Int(u, v);
			printf("%lld\n", hld_query(u, v));
		}
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
