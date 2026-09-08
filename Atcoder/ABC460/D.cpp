#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int inf = 1000000010;
vector<int> dx = { 1,0,-1,0,1,-1,-1,1 }, dy = { 0,1,0,-1,1,1,-1,-1 };

int main() {
	int n, m;
	cin >> n >> m;
	vector<string> a(n);
	rep(i, n) cin >> a[i];

	auto in = [&](int x, int y) {return 0 <= x && x < n && 0 <= y && y < m; };

	vector<string> b(n, string(m, '.'));
	rep(i, n) rep(j, m) {
		if (a[i][j] == '#') {
			rep(d, 8) {
				int x = i + dx[d], y = j + dy[d];
				if (in(x, y) && a[x][y] == '.') b[x][y] = '#';
			}
		}
	}
	a = move(b);

	vector D(n, vector<int>(m, inf));
	queue<pair<int, int>> Q;
	rep(i, n) rep(j, m) if (a[i][j] == '#') { D[i][j] = 0; Q.push({ i, j }); }
	while (!Q.empty()) {
		auto [i, j] = Q.front(); Q.pop();
		rep(d, 8) {
			int x = i + dx[d], y = j + dy[d];
			if (in(x, y) && D[x][y] == inf) {
				D[x][y] = D[i][j] + 1;
				Q.push({ x, y });
			}
		}
	}
	rep(i, n) {
		rep(j, m) a[i][j] = (D[i][j] % 2 == 0 ? '.' : '#');
		cout << a[i] << '\n';
	}
}
