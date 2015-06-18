#include <iostream>
#include <vector>

using namespace std;

int n;
int m;
vector<vector<int> > edges;
int matched[100005];
int visited[100005];

vector<int> path;
bool pathFound;

void augment(vector<int> path) {
	for (int i = 0; i < path.size() - 1; i+=2) {
		int u = path[i];
		int v = path[i+1];
		matched[u] = v;
		matched[v] = u;
	}
}

void dfs(int u, int side) {
	if (pathFound || visited[u]) return;

	visited[u] = true;
	path.push_back(u);

	if (side == 1) {
		if (!matched[u]) {
			pathFound = true;
			augment(path);
		} else {
			dfs(matched[u], !side);
		}
	} else {
		for (int i = 0; i < edges[u].size(); i++) {
			int v = edges[u][i];
            dfs(v, !side);
		}
	}
	path.pop_back();
}

void matching() {
    for (int u = 1; u <= n; u++) {
		if (!matched[u]) {
			pathFound = false;
			memset(visited, 0, sizeof(visited));
			dfs(u, 0);
		}
	}

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (matched[i]) {
            count++;
        }
    }
    cout << count << endl;
}

int main() {
	int k;
	cin >> n >> m >> k;
	edges = vector< vector<int> >(n + m + 1, vector<int>() );

	for (int i = 0; i < k; i++) {
		int u, v;
		cin >> u >> v;
		v += n;

		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	matching();
}
/*
5 4 6
5 2
1 2
4 3
3 1
2 2
4 4
*/
