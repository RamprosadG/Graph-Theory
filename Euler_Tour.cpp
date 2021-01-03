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

int t = 0;
std::vector<int> g[N];
int par[M][N], st[N], et[N], dep[N];
ll a[N], node[4 * N];

void propagate(int pos) {
	node[pos * 2] += node[pos];
	node[pos * 2 + 1] += node[pos];
	node[pos] = 0;
}

void update(int pos, int left, int right, int x, int y, int val) {
	if (left > y or right < x) return;
	if (left >= x and right <= y) {
		node[pos] += val;
		return;
	}
	if (node[pos]) propagate(pos);
	int mid = (left + right) >> 1;
	update(pos * 2, left, mid, x, y, val);
	update(pos * 2 + 1, mid + 1, right, x, y, val);
}

int query(int pos, int left, int right, int x) {
	if (left > x or right < x) return 0;
	if (left == right) return node[pos];
	if (node[pos]) propagate(pos);
	int mid = (left + right) >> 1;
	int m = query(pos * 2, left, mid, x);
	int n = query(pos * 2 + 1, mid + 1, right, x);
	return m + n;
}

void dfs(int u, int p = -1, int d = 0) {
	st[u] = ++t;
	dep[u] = d;
	for (int i = 1; i < M; i++) {
		par[i][u] = par[i - 1][par[i - 1][u]];
	}
	for (int v : g[u]) {
		if (p == v) continue;
		par[0][v] = u;
		dfs(v, u, d + 1);
	}
	et[u] = t;
}

int lca(int u, int v) {
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

ll get_result(int u, int v, int n) {
	int l = lca(u, v);
	ll ans = 0;
	ans += query(1, 1, n, st[u]);
	ans += query(1, 1, n, st[v]);
	ans -= 2 * query(1, 1, n, st[l]);
	return ans + a[l];
}

int solve() {
	int n, q; Int(n, q);
	for (int i = 1; i <= n; i++) {
		Int(a[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v; Int(u, v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(n, 1, 1);
	for (int i = 1; i <= n; i++) {
		update(1, 1, n, st[i], et[i], a[i]);
	}
	while (q--) {
		int ck; Int(ck);
		if (ck) {
			int u, v; Int(u, v);
			printf("%lld\n", get_result(u, v, n));
		}
		else {
			int u, val; Int(u, val);
			a[u] += val;
			update(1, 1, n, st[u], et[u], val);
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
