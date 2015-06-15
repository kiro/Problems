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
    int value;
    interval range;
    node *left, *right;

    node(int value, interval range, node *left, node *right) : value(value), range(range), left(left), right(right) {
    }

    // recursively construct full index tree
    node(int value, interval range) : value(value), range(range) {
        if (range.from != range.to) {
            left = new node(0, interval(range.from, range.mid));
            right = new node(0, interval(range.mid + 1, range.to));
        } else {
            left = right = NULL;
        }
    }
};

struct index_tree {
    node *root;

    index_tree() : root(NULL) {}

    index_tree(int n) {
        root = new node(0, interval(0, n-1));
    }

    int sum(node *current, interval query) {
        if (query.contains(current->range)) {
            return current->value;
        } else if (query.intersects(current->range)) {
            return sum(current->left, query) + sum(current->right, query);
        }
        return 0;
    }

    node* set(node *current, int index, int newValue) {
        if (current->range.is(index)) {
            return new node(newValue, current->range, NULL, NULL);
        } else if (current->range.contains(index)) {
            node *left = set(current->left, index, newValue);
            node *right = set(current->right, index, newValue);

            return new node(left->value + right->value, current->range, left, right);
        }
        return current;
    }

    int sum(interval range) {
        return sum(root, range);
    }

    index_tree set(int index, int value) {
        index_tree result;
        result.root = set(root, index, value);;
        return result;
    }

    void print(node *current, int depth) {
        if (current != NULL) {
            print(current->left, depth + 1);
            print(current->right, depth + 1);
        }
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
        tree = tree.set(j, value);
        tree.print(tree.root, 0);
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
}
