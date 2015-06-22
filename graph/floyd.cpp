#include <iostream>

using namespace std;

int n, m;
int g[1000][1000];

void floyd() {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][k] && g[k][j]) {
					int d = g[i][k] + g[k][j];

					g[i][j] = g[i][j] ? min(g[i][j], d) : d;
				}
			}
		}
	}
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		g[u][v] = g[v][u] = c;
	}

	floyd();

	cout << g[0][5] << endl;
}
