#include <iostream> 
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> g(1000);
int in[1000];

void topsort() {
	queue<int> q;

	// add the tasks that don't have dependencies
	for (int i = 0; i < n; i++)	{
		in (in[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int u = q.top();
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
		in[v]++;
	}

	topsort();
}