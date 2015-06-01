#include <iostream>
#include <vector>

using namespace std;

vector<int> sub(vector<int> arr, int from, int to) {
    vector<int> result;
    for (int i = from; i < to; i++) {
        result.push_back(arr[i]);
    }
    return result;
}

vector<int> concat(vector<int> left, vector<int> right) {
    for (int i = 0; i < right.size(); i++) {
        left.push_back(right[i]);
    }
    return left;
}

int main() {
  int n, m;

  cin >> n >> m;

  vector<int> arr;

  for (int i = n; i >= 1; i--) {
    arr.push_back(i);
  }

  for (int i = 0; i < m; i++) {
    int p, q, r;
    cin >> p >> q >> r;

    arr = concat(sub(arr, p + q + r, arr.size()),
                 concat(sub(arr, p + q, p + q + r),
                        concat(sub(arr, p, p + q), sub(arr, 0, p))
                 )
           );
  }

  cout << arr[0] << endl;
}
