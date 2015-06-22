#include <iostream>
#include <vector>

using namespace std;

struct setunion {
	vector<int> parent;
	vector<int> depth;

	setunion() {
        parent = vector<int>(1000);
        depth = vector<int>(1000, 1);
		for (int i = 0; i < 1000; i++) {
			// each node is a separate set initially
			parent[i] = i;
		}
	}

	int root(int i) {
		int r = i;
		// find the root
		while (r != parent[r]) r = parent[r];

		// relink the children along the path to the root
		while (i != parent[i]) {
			int p = parent[i];
			parent[i] = r;
			i = p;
		}

		return r;
	}

	void merge(int i, int j) {
		int ri = root(i);
		int rj = root(j);

		if (depth[ri] < depth[rj]) {
			parent[ri] = rj;
		} else {
			parent[rj] = ri;
			// if depth is equal increase the depth of ri
			if (depth[ri] == depth[rj]) depth[ri]++;
		}
	}
};

struct edge {
	int u, v, c;

	edge(int u, int v, int c) : u(u), v(v), c(c) {}
};

bool compare(edge left, edge right) {
	return left.c < right.c;
}

void kruskal(vector<edge> edges) {
	sort(edges.begin(), edges.end(), compare);

	setunion s;

	int mst = 0;

	for (int i = 0; i < edges.size(); i++) {
		edge e = edges[i];

		if (s.root(e.u) != s.root(e.v)) {
			mst += e.c;
			// use the edge somehow
			s.merge(e.u, e.v);
		}
	}

	cout << mst << endl;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<edge> edges;
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;

		edges.push_back(edge(u, v, c));
		edges.push_back(edge(v, u, c));
	}

	kruskal(edges);
}
