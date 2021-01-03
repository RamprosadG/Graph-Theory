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
const int N   = (int) 1e3 + 5;

int n, m, s, t;

vector<int> g[N];
ll cf[N][N];
int dis[N], idx[N];

bool bfs() {
	queue<int>q;
	q.push(s);
	for (int i = 1; i <= n; i++) {
		dis[i] = -1;
	}
	dis[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : g[u]) {
			if (dis[v] == -1 and cf[u][v] > 0) {
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
	return (dis[t] != -1);
}

ll dfs(int u, ll cap) {
	if (cap == 0) return 0;
	if (u == t) return cap;
	for (int& i = idx[u]; i < sz(g[u]); i++) {
		int v = g[u][i];
		if (dis[u] + 1 != dis[v] or cf[u][v] < 1) continue;
		ll flow = dfs(v, min(cap, cf[u][v]));
		if (flow == 0) continue;
		cf[u][v] -= flow;
		cf[v][u] += flow;
		return flow;
	}
	return 0;
}

ll maximum_flow() {
	ll flow = 0;
	while (1) {
		if (!bfs()) break;
		for (int i = 1; i <= n; i++) {
			idx[i] = 0;
		}
		while (ll cap = dfs(s, inf)) {
			flow += cap;
		}
	}
	return flow;
}

int solve() {
	Int(n, m);
	for (int i = 1; i <= m; i++) {
		int u, v; ll w; Int(u, v, w);
		g[u].push_back(v);
		g[v].push_back(u);
		cf[u][v] = w;
	}
	Int(s, t);
	printf("%lld\n", maximum_flow());
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
