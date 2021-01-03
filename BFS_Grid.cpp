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
const int N   = (int) 2e3 + 5;

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
string s[N];

bool valid(int n, int m, int x, int y) {
	if (x >= 0 and x < n and y >= 0 and y < m) return true;
	return false;
}

int dis[N][N];
bool vis[N][N];
pii par[N][N];

void bfs(int n, int m, int u, int v) {
	queue<pii>q;
	q.push(mp(u, v));
	vis[u][v] = true;
	while (!q.empty()) {
		u = q.front().ff, v = q.front().ss;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int x = u + dr[i], y = v + dc[i];
			if (valid(n, m, x, y) and s[x][y] == '.' and !vis[x][y]) {
				dis[x][y] = dis[u][v] + 1;
				par[x][y] = mp(u, v);
				vis[x][y] = true;
				q.push(mp(x, y));
			}
		}
	}
}

void path(int u, int v, int x, int y) {
	if (par[x][y] != mp(-1, -1)) path(u, v, par[x][y].ff, par[x][y].ss);
	if (u == x && v == y) printf("(%d %d)", x + 1, y + 1);
	else printf(" (%d %d)", x + 1, y + 1);
}

int solve() {
	int n, m; Int(n, m);
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			par[i][j] = { -1, -1};
		}
	}
	int u, v; Int(u, v); u--, v--;
	bfs(n, m, u, v);
	int q; Int(q);
	while (q--) {
		int x, y; Int(x, y); x--, y--;
		if (vis[x][y]) {
			printf("%d\n", dis[x][y]);
			path(u, v, x, y);
			printf("\n");
		}
		else printf("Impossible\n");
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
