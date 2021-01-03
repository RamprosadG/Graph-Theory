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
const int M   = (int) 500 + 5;

vector<int> g[N];
int dis[M], sz[N];
bool vis[N];
int n, k, nd;
ll ans;

void upd_dis(int u, int p, int d) {
	if (d > k)  return;
	dis[d]++;
	for (auto v : g[u]) {
		if (v != p and !vis[v]) upd_dis(v, u, d + 1);
	}
}

void upd_res(int u, int p, int d) {
	if (d > k)  return;
	ans += dis[k - d];
	for (auto v : g[u]) {
		if (v != p and !vis[v]) upd_res(v, u, d + 1);
	}
}

void getsz(int u, int p = -1) {
	sz[u] = 1, nd++;
	for (auto v : g[u]) {
		if (v != p and !vis[v]) getsz(v, u), sz[u] += sz[v];
	}
}

int centroid(int u, int p = -1) {
	for (auto v : g[u]) {
		if (v != p and !vis[v] and sz[v] > nd / 2) return centroid(v, u);
	}
	return u;
}

void decompose(int u) {
	memset(dis, 0, sizeof(dis));
	nd = 0, dis[0]++;
	getsz(u);
	int center = centroid(u);
	vis[center] = true;
	for (auto v : g[center]) {
		if (!vis[v]) {
			upd_res(v, center, 1);
			upd_dis(v, center, 1);
		}
	}
	for (auto v : g[center]) {
		if (!vis[v]) decompose(v);
	}
}

int solve() {
	Int(n, k);
	for (int i = 1; i < n; i++) {
		int u, v; Int(u, v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	decompose(1);
	printf("%lld\n", ans);
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
