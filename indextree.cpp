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

    int sum(int from, int to) {
        return sum(root, interval(from, to));
    }

    void set(int index, int value) {
        set(root, index, value);
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
