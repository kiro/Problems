#include <iostream>
#include <cstdlib>
#include <utility>
#include <queue>

using namespace std;

struct node {
    int value;
    int priority;
    node *left;
    node *right;

    node(int value) : value(value), priority(rand()), left(NULL), right(NULL) {
    }

    void rotateLeft() {
        node *leftLeft = left->left;
        node *leftRight = left->right;
        node *prevRight = right;

        swap(value, left->value);
        swap(priority, left->priority);
        right = left;
        left = leftLeft;

        right->right = prevRight;
        right->left = leftRight;
    }

    void rotateRight() {
        node *rightLeft = right->left;
        node *rightRight = right->right;
        node *prevLeft = left;

        swap(value, right->value);
        swap(priority, right->priority);
        left = right;
        right = rightRight;

        left->left = prevLeft;
        left->right = rightLeft;
    }
};

struct treap {
    node *root;

    treap() : root(NULL) { }

    void insert(node **current, int value) {
        if (*current == NULL) {
            (*current) = new node(value);
        } else {
            node *currentNode = *current;
            if (currentNode->value > value) {
                insert(&currentNode->left, value);

                if (currentNode->left->priority > currentNode->priority) {
                    currentNode->rotateLeft();
                }
            } else if (currentNode->value < value) {
                insert(&currentNode->right, value);

                if (currentNode->right->priority > currentNode->priority) {
                    currentNode->rotateRight();
                }
            }
        }
    }

    void insert(int value) {
        insert(&root, value);
    }

    pair<node*, node*> find(node* parent, node *current, int value) {
        if (current == NULL) {
            return make_pair((node*)NULL, (node*)NULL);
        }
        if (current->value < value) {
            return find(current, current->right, value);
        } else if (current->value > value) {
            return find(current, current->left, value);
        }
        return make_pair(parent, current);
    }

    void remove(int value) {
        pair<node*, node*> nodes = find(NULL, root, value);

        node *parent = nodes.first;
        node *n = nodes.second;

        if (n == NULL) return;

        while (n->left != NULL || n->right != NULL) {
            parent = n;

            if (n->left != NULL && (n->right == NULL || n->left->priority > n->right->priority)) {
                n->rotateLeft();
                n = n->right;
            } else if (n->right != NULL) {
                n->rotateRight();
                n = n->left;
            }
        }

        if (parent == NULL) { // remove the root
            delete root;
            root = NULL;
        } else { // otherwise remove a leaf
            if (parent->left == n) parent->left = NULL;
            if (parent->right == n) parent->right = NULL;
            delete n;
        }
    }

    bool contains(int value) {
        pair<node*, node*> position = find(NULL, root, value);

        return position.second != NULL;
    }

    void print(node *node) {
        if (node != NULL) {
            cout << "( " << node->value << ", " << node->priority << " ) ";
            print(node->left);
            print(node->right);
        }
    }

    void print() {
        print(root);
        cout << endl;
    }
};

int main() {
    treap t;

    for (int i = 1; i < 5; i++) {
        t.insert(i);
        t.print();
    }

    for (int i = -2; i <= 10; i++)
        cout << t.contains(i) << " ";
    cout << endl;
}
