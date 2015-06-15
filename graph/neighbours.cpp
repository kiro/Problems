#include <iostream>
#include <vector>

using namespace std;

int n, m;
// Списък на съседите
vector<vector<int> > g;

void output() {
	for (int i = 0; i < n; i++) {
		cout << "Neighbours of " << i << " :";
		for (int j = 0; j < g[i].size(); j++) {
			cout << " " << g[i][j];
		}
		cout << endl;
	}
}

int main() {
	cin >> n >> m;
	g = vector<vector<int> >(n);

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;

		g[u].push_back(v);
	}

	output();
}