#include <iostream>
#include <queue>

using namespace std;

int n, m;
vector<vector<int> > g(1000);
int in[1000];

void topsort() {
	queue<int> q;

	for (int i = 0; i < n; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            in[ g[i][j] ]++;
        }
	}

	// add the tasks that don't have dependencies
	for (int i = 0; i < n; i++)	{
		if (in[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		cout << u << " ";

		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];

			if (--in[v] == 0) {
				q.push(v);
			}
		}
	}

	cout << endl;
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;

		g[u].push_back(v);
	}

	topsort();
}

/**
6 7
0 5
0 3
1 0
2 4
2 5
4 3
5 4
*/
