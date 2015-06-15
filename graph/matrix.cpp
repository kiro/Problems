#include <iostream>

using namespace std;

// Матрица на съседство
int MAX = 100;

int g[MAX][MAX];
int n, m; 

void output() {
	for (int i = 0; i < n; i++) {
		cout << "Съседи на " << i << " :"; 
		for (int j = 0; j < n; j++) {
			if (g[i][j]) {
				cout << " " << j;
			}			
		}
		cout << endl;
	}
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g[u][v] = 1;
		// g[v][u] = 1; ако е неориентиран
		// може и 
		// cin >> u >> v >> g[u][v]; ако е ориентиран с тегла
	}

	output();
}

