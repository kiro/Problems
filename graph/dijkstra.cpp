#include <iostream>

using namespace std;

int MAX = 1000000;
int n;
int g[1000][1000];

int dijkstra(int start, int end) {
	// dist contains the minimal distance from start to the i-th node, for now
	vector<int> dist(1000, MAX);
	vector<bool> visited(1000, false);

	dist[start] = 0;

	while (true) {
		// find not visited node which has minimal dist
		int u = -1;

		for (int i = 0; i < n; i++) {
			if (!visited[i] && (u == -1 || dist[i] < dist[u]) ) {
				u = i;
			}
		}	

		if (u == -1) break; // all nodes are visited
		// mark it as visited
		visited[u] = true;

		// update the dist for its neighbours
		for (int i = 0; i < n; i++) {
			if (g[u][i]) {				
				dist[i] = min(dist[i], dist[u] + g[u][i]);
			}
		}
	}	

	// at the end dist[i] contains the min distance from start to node i
	return dist[end];
}

int main() {

}