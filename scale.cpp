#include <iostream>
#include <vector>

using namespace std;

int sums[20];
long long pow[20];
vector<vector<int> > scales(2);

int firstPower(int n) {
    for (int i = 0; i < 20; i++) {
        if (sums[i] >= n) {
            return pow[i];
        }
    }
    return 0;
}

void f(int n, int side) {
    int k = firstPower(n);

    scales[side].push_back(k);

    if (k < n) {
        f(n - k, side);
    } else if (k > n) {
        f(k - n, !side);
    }
}

int main() {
    sums[0] = pow[0] = 1;

    for (int i = 1; i < 20; i++) {
        pow[i] = pow[i-1] * 3;
        sums[i] = sums[i-1] + pow[i];
    }

    char side;
    int n;
    cin >> side >> n;
    f(n, side == 'L');
    cout << "L:";
    for (int i = scales[0].size() - 1; i >= 0; i--) {
        cout << scales[0][i] << " ";
    }
    cout << endl << "R:";
    for (int i = scales[1].size() - 1; i >= 0; i--) {
        cout << scales[1][i] << " ";
    }
    cout << endl;
}
