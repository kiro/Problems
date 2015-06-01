#include <iostream>
#include <cmath>

using namespace std;

int **arr;
int **dp;
int n, m;

int f(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return 100000000;
    } else if (j == 0) {
        dp[i][j] = arr[i][j];
    } else if (dp[i][j] == 0) {
        dp[i][j] = arr[i][j] + min(f(i-1, j-1), min(f(i, j-1), f(i+1, j-1)));
    }
    return dp[i][j];
}

int main() {
    cin >> n >> m;

    dp = new int*[n];
    arr = new int*[n];

    for (int i = 0; i < n; i++) {
        dp[i] = new int[m];
        arr[i] = new int[m];

        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            dp[i][j] = 0;
        }
    }

    int result = -1;
    for (int i = 0; i < n; i++) {
        int val = f(i, m - 1);
        result = result == -1 ? val : min(result, val);
    }

    cout << result;
}
