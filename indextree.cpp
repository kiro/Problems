#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

struct interval {
    int from, to;

    interval(int from, int to) : from(from), to(to) {
    }

    bool contains(interval other) {
        return from <= other.from && to >= other.to;
    }

    bool intersects(interval other) {
        return other.from <= to && other.to >= from;
    }

    bool contains(int value) {
        return from <= value && value <= to;
    }
};

class index_tree {
	private:
		int n;
		vector<int> nodes;

		int sum(int i, interval current, interval query) {
            if (query.contains(current)) {
				return nodes[i];
			}
			if (query.intersects(current)) {
				int mid = (current.from + current.to) / 2;

                return sum(i * 2 + 1, interval(current.from, mid), query) +
                       sum(i * 2 + 2, interval(mid + 1, current.to), query);
			}
			return 0;
		}

		int set(int i, interval current, int index, int value) {
		    if (current.from == current.to && current.from == index) {
                nodes[i] = value;
		    } else if (current.contains(index)) {
                int mid = (current.from + current.to) / 2;

                nodes[i] = set(i * 2 + 1, interval(current.from, mid), index, value) +
                           set(i * 2 + 2, interval(mid + 1, current.to), index, value);
            }

            return nodes[i];
		}
	public:
		index_tree(int n) : n(n) {
			nodes = vector<int>(3 * n);
		}

		int sum(int from, int to) {
			return sum(0, interval(0, n - 1), interval(from, to));
		}

		void set(int index, int value) {
            set(0, interval(0, n - 1), index, value);
		}
};

int main() {
    int n = 10;
    index_tree tree(n);

    for (int i = 0; i < n; i++) {
        tree.set(i, i + 1);
    }

    for (int i = 0; i < 10; i++) {
    	for (int j = i; j < 10; j++) {
    		cout << i << " " << j << " " << tree.sum(i, j) << endl;
    	}
    }
}
