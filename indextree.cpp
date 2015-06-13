#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

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

struct index_tree {
    node root;
    vector<int> value;

    index_tree(int n) {
        value = vector<int>(3 * n);
        root = node(0, interval(0, n-1));
    }

    int sum(node current, interval query) {
        if (query.contains(current.range)) {
            return value[current.index];
        } else if (query.intersects(current.range)) {
            return sum(current.left(), query) + sum(current.right(), query);
        }
        return 0;
    }

    int set(node current, int index, int newValue) {
        if (current.range.is(index)) {
            value[current.index] = newValue;
        } else if (current.range.contains(index)) {
            value[current.index] = set(current.left(), index, newValue) + set(current.right(), index, newValue);
        }
        return value[current.index];
    }

    int sum(interval range) {
        return sum(root, range);
    }

    void set(int index, int value) {
        set(root, index, value);
    }
};

struct rect {
    interval xrange;
    interval yrange;

    rect(interval xrange, interval yrange) : xrange(xrange), yrange(yrange) {}
};

struct point {
    int x, y;
    point(int x, int y) : x(x), y(y) {}
};

struct twod_index_tree {
    node root;
    vector<vector<int> > arr;
    vector<index_tree> value;

    twod_index_tree(int n, int m) {
        value = vector<index_tree>(3*n, index_tree(m));
        arr = vector<vector<int> >(n, vector<int>(m));
        root = node(0, interval(0, n-1));
    }

    int sum(node current, rect query) {
        if (query.xrange.contains(current.range)) {
            return value[current.index].sum(query.yrange);
        } else if (query.xrange.intersects(current.range)) {
            return sum(current.left(), query) + sum(current.right(), query);
        }
        return 0;
    }

    void set(node current, point p, int diff) {
        if (current.range.contains(p.x)) {
            // add the diff to the current value
            int v = value[current.index].sum(interval(p.y, p.y));
            value[current.index].set(p.y, v + diff);

            if (!current.range.is(p.x)) {
                set(current.left(), p, diff);
                set(current.right(), p, diff);
            }
        }
    }

    int sum(rect range) {
        return sum(root, range);
    }

    void set(point p, int value) {
        int diff = value - arr[p.x][p.y];
        arr[p.x][p.y] = value;

        set(root, p, diff);
    }
};

int main() {
    int n = 10;
    index_tree tree(n);
    vector<int> values(n);

    // fill it randomly
    for (int i = 0; i < 2*n; i++) {
        int j = rand() % n;
        int value = rand() % n;
        values[j] = value;
        tree.set(j, value);
    }

    // test all intervals
    for (int i = 0; i < n; i++) {
    	for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += values[k];
            }
            int idxsum = tree.sum(interval(i, j));

            if (sum != idxsum) {
                cout << i << " " << j << " " << sum << " " << idxsum << endl;
            }
    	}
    }

    twod_index_tree plane(n, n);
    // fill it randomly
    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < 2*n; j++) {
            int x = rand() % n;
            int y = rand() % n;
            int value = rand() % n;
            plane.set(point(x, y), value);
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
                            sum += plane.arr[x][y];
                        }
                    }

                    int idxsum = plane.sum(rect(interval(x0, x1), interval(y0, y1)));
                    if (sum != idxsum) {
                        cout << x0 << " " << x1 << " " << y0 << " " << y1 << " " << sum << " " << idxsum << endl;
                    }
                }
            }
        }
    }
}
