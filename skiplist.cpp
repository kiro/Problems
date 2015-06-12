#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
	int value;
	map<int, node*> next;

	node(int value) : value(value) {}
};

struct skiplist {
    node *first;

    skiplist() {
        first = new node(-1);
    }

    void insert(node *current, node *newNode, int level) {
        if (level < 0) return;

        if (current->next[level] == NULL || current->next[level]->value > newNode->value) {
            newNode->next[level] = current->next[level];
            current->next[level] = newNode;
            insert(current, newNode, level - 1);
        } else {
            insert(current->next[level], newNode, level);
        }
    }

    node * find(node *current, int value, int level) {
        if (level < 0) return NULL;
        if (current->value == value) return current;

        if (current->next[level] == NULL || current->next[level]->value > value) {
            return find(current, value, level - 1);
        } else {
            return find(current->next[level], value, level);
        }
    }

    node * find(int value) {
        return find(first, value, first->next.size() - 1);
    }

    void remove(node *current, node* n, int level) {
        if (level < 0) return;

        if (current->next[level]->value == n->value) {
            current->next[level] = n->next[level];
            remove(current, n, level - 1);
        } else {
            remove(current->next[level], n, level);
        }
    }

    void remove(int value) {
        node* valueNode = find(value);
        if (valueNode == NULL) return;
        remove(first, valueNode, valueNode->next.size() - 1);
        delete valueNode;
    }

    void insert(int value) {
        node* valueNode = find(value);
        if (valueNode != NULL) return;

        int level = 0;
        while (rand() % 2 == 1) level++;

        insert(first, new node(value), level);
    }

    void print(node *node, int level) {
        if (node != NULL) {
            cout << node->value << " ";
            print(node->next[level], level);
        }
    }

    void print() {
        for (int i = first->next.size() - 1; i >= 0; i--) {
            print(first, i);
            cout << endl;
        }
        cout << endl;
        for (int i = 1; i <= 10; i++) {
            cout << (find(i) != NULL) << " ";
        }
        cout << endl;
    }
};

int main() {
    skiplist s;

    s.insert(5);
    s.insert(2);
    s.print();

    s.insert(9);
    s.insert(3);
    s.insert(1);
    s.insert(6);
    s.insert(10);

    s.print();

    s.remove(10);
    s.print();
    s.remove(11);
    s.print();
    s.remove(1);
    s.print();
    s.remove(3);
    s.print();
    s.remove(6);
    s.print();
}
