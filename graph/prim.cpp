#include <iostream> 

using namespace std;

int n, m;
int g[1000][1000];

void prim() {
	vector<int> visited(1000, 0);
	// add 0 the mst 
	visited[0] = 1;

	int cost = 0;

	// add n - 1 edges
	for (int k = 0; k < n - 1; k++) {		
		// find minimum edge that connects node in the mst with a node outside
		int c = 10000, u, v;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j] && visited[i] && !visited[j] && g[i][j] < c) {
					c = g[i][j];
					u = i;
					v = j;
				}
			}
		}

		cost += c;
		visited[v] = true;
	}

	cout << cost << endl;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v >> g[u][v];
	}

	prim();
}