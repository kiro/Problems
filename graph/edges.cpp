#include <iostream>
#include <vector>

using namespace std;

// Списък на ребрата
struct edge {
	int u, v;
};

int n, m;
vector<edge> edges;

int main() {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		edge e;
		cin >> e.u >> e.v;
		edges.push_back(e);
	}
}

