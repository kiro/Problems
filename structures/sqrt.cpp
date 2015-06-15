#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct sqrt_index {
	int n;
	int sqrtn;

	vector<int> arr;
	vector<int> sqr;

	sqrt_index(int length) {
		n = length;
		sqrtn = (int)sqrt(n);

		arr = vector<int>(n);
		sqr = vector<int>(n/sqrtn + 1);
	};

	void set(int index, int value) {
		int diff = value - arr[index];
		arr[index] = value;
		sqr[index / sqrtn] += diff;
	}

	int sum(int from, int to) {
		int result = 0;
		for (int i = from; i <= to;) {
			if (i % sqrtn == 0 && i + sqrtn < to) {
				result += sqr[i / sqrtn];
				i += sqrtn;
			} else {
				result += arr[i];
				i++;
			}
		}

		return result;
	}
};

int main() {
	int n = 10;
	sqrt_index idx(n);

	for (int i = 0; i < n; i++) {
        idx.set(i, rand() % 10);
	}

	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int sum = 0;
			for (int k = i; k <= j; k++) {
				sum += idx.arr[k];
			}

			int idxsum = idx.sum(i, j);
			if (idxsum != sum) {
				cout << i << " " << j << " " << idxsum << " " << sum << endl;
			}
		}
	}


}
