#include <iostream>
#include <vector>
using namespace std;

struct interval {
    int from, to, mid;

    interval() {}
    interval(int from, int to) : from(from), to(to), mid( (from+to) / 2 ) {
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

    bool is(int value) {
        return from == value && to == value;
    }
};

struct node {
    int index;
    interval range;

    node() {}
    node(int index, interval range) : index(index), range(range) {}

    node left() {
        return node(index * 2 + 1, interval(range.from, range.mid));
    }
    node right() {
        return node(index * 2 + 2, interval(range.mid + 1, range.to));
    }
};

struct counter {
	int value;

	void set(vector<int> index, int newValue) {
		value = newValue;
	}

	int sum(vector<interval> range) {
		return value;
	}
};

template<class T, int n, int d>
struct t_index_tree {
    node root;
    vector<T> value;

    t_index_tree() {
        value = vector<T>(3 * n);
        root = node(0, interval(0, n-1));
    }

    int sum(node current, vector<interval> query) {
        if (query[d].contains(current.range)) {
            return value[current.index].sum(query);
        } else if (query[d].intersects(current.range)) {
            return sum(current.left(), query) + sum(current.right(), query);
        }
        return 0;
    }

    int set(node current, vector<int> index, int newValue) {
        if (current.range.is(index[d])) {
            value[current.index].set(index, newValue);
        } else if (current.range.contains(index[d])) {
            value[current.index].set(index, set(current.left(), index, newValue) + set(current.right(), index, newValue));
        }

        vector<interval> intervals;
        for (int i = 0; i < index.size(); i++) {
        	intervals.push_back(interval(index[i], index[i]));
        }
        return value[current.index].sum(intervals);
    }

    int sum(vector<interval> range) {
        return sum(root, range);
    }

    void set(vector<int> index, int value) {
        set(root, index, value);
    }
};

int main() {
    int n = 10;
    t_index_tree<counter, 10, 0> tree;
    vector<int> values(n);

    // fill it randomly
    for (int i = 0; i < 2*n; i++) {
        int j = rand() % n;
        int value = rand() % n;
        values[j] = value;
        vector<int> idx(1, j);
        tree.set(idx, value);
    }

    // test all intervals
    for (int i = 0; i < n; i++) {
    	for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += values[k];
            }
            int idxsum = tree.sum(vector<interval>(1, interval(i, j)));

            if (sum != idxsum) {
                cout << i << " " << j << " " << sum << " " << idxsum << endl;
            }
    	}
    }

    vector<vector<int> > arr(n, vector<int>(n));
    //twod_index_tree plane(n, n);

    t_index_tree<t_index_tree<counter, 10, 1>, 10, 0> plane;

    // fill it randomly
    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < 2*n; j++) {
            int x = rand() % n;
            int y = rand() % n;
            int value = rand() % n;
            arr[x][y] = value;
            vector<int> idx(2, 0);
            idx[0] = x;
            idx[1] = y;
            plane.set(idx, value);
        }
    }

    // test all the intervals
    for (int x0 = 0; x0 < n; x0++) {
        for (int x1 = x0; x1 < n; x1++) {
            for (int y0 = 0; y0 < n; y0++) {
                for (int y1 = y0; y1 < n; y1++) {

                    int sum = 0;
                    for (int x = x0; x <= x1; x++) {
                        for (int y = y0; y <= y1; y++) {
                            sum += arr[x][y];
                        }
                    }

                    vector<interval> range(2, interval(0, 0));
                    range[0] = interval(x0, x1);
                    range[1] = interval(y0, y1);

                    int idxsum = plane.sum(range);

                    if (sum != idxsum) {
                        cout << x0 << " " << x1 << " " << y0 << " " << y1 << " " << sum << " " << idxsum << endl;
                    }
                }
            }
        }
    }
}

