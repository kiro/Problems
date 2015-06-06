#include <iostream>
#include <cstdio>

using namespace std;

const int letters = 26;

struct node {
    bool isEnd;
    node* next[letters];
};

node *root = new node();

void add(string s, int i, node *current) {
    if (i == s.size()) {
        current->isEnd = true;
        return;
    }

    int letter = s[i] - 'a';
    if (current->next[letter] == NULL) {
        current->next[letter] = new node();
    }

    add(s, i + 1, current->next[letter]);
}

void add(string s) {
    add(s, 0, root);
}

void match(string regex, int i, node *current, string prefix) {
    if (current == NULL) {
        return;
    }

    if (i == regex.size()) {
        if (current->isEnd) {
            printf("%s\n", prefix.c_str());
        }
        return;
    }

    if (regex[i] == '?') {
        for (int j = 0; j < letters; j++) {
            match(regex, i + 1, current->next[j], prefix + char('a' + j));
        }
    } else if (regex[i] == '*') {
        match(regex, i + 1, current, prefix); // skip the *

        for (int j = 0; j < letters; j++) { // match a letter with the star
            match(regex, i, current->next[j], prefix + char('a' + j));
        }
    } else { // match the current letter
        match(regex, i + 1, current->next[regex[i] - 'a'], prefix + regex[i]);
    }
}

void match(string regex) {
    printf("%s\n", regex.c_str());
    match(regex, 0, root, "");
    printf("\n");
}

int main() {
    char* arr[] = {"aaaa", "abc", "acd", "abd", "c", "cdaa", "cdbb", "cxxx", "cxy", "cxyyy" };

    for (int i = 0; i < 10; i++) {
        add(arr[i]);
    }

    match("*");
    match("a");
    match("a*");
    match("a??");
    match("ac*");
    match("c*?");
    match("c*x?");
}
