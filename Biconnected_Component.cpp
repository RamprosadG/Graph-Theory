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

std::vector<int> g[N];
std::vector<pii> bcc[N];
int d[N], low[N], par[N], vis[N], t, k;
stack<pii> st;

void dfs(int u) {
	vis[u] = 1;
	d[u] = low[u] = ++t;
	int child = 0;
	for (int v : g[u]) {
		if (!vis[v]) {
			st.push({u, v});
			par[v] = u;
			child++;
			dfs(v);
			smin(low[u], low[v]);
			if ((d[u] == 1 and child > 1) or (d[u] > 1 and low[v] >= d[u])) {
				++k;
				while (st.top().ff != u or st.top().ss != v) {
					bcc[k].push_back(st.top());
					st.pop();
				}
				bcc[k].push_back(st.top());
				st.pop();
			}
		}
		else if (v != par[u]) {
			low[u] = min(low[u], d[v]);
			if (d[v] < d[u]) {
				st.push({u, v});
			}
		}
	}
}

void biconnected(int n) {
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			t = 0;
			dfs(i);
			if (sz(st) > 0) {
				++k;
				while (!st.empty()) {
					bcc[k].push_back(st.top());
					st.pop();
				}
			}
		}
	}
}

int solve() {
	int n, m; Int(n, m);
	for (int i = 0; i < m; i++) {
		int u, v; Int(u, v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	biconnected(n);
	printf("%d\n", k);
	for (int i = 1; i <= k; i++) {
		for (auto x : bcc[i]) {
			printf("(%d %d) ", x.ff, x.ss);
		}
		printf("\n");
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
