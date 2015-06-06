#include <iostream>
#include <cstdlib>

using namespace std;

bool is_number(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

bool is_operator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char op) {
	return (op == '+' || op == '-') ? 1 : 2;
}

int apply(char op, int left, int right) {
	switch(op) {
		case '+' : return left + right;
		case '-' : return left - right;
		case '*' : return left * right;
		case '/' : return left / right;
	}
	return -1;
}

int calc(string expr) {
	if (is_number(expr)) {
		return atoi(expr.c_str());
	}

	int depth = 0, split = 0;
	for (int i = 0; i < expr.size(); i++) {
		if (expr[i] == '(') {
			depth++;
		} else if (expr[i] == ')') {
		 	depth--;
		} else if (depth == 0 && is_operator(expr[i]) && (!split || priority(expr[i]) < priority(expr[split]))) {
			split = i;
		}
	}

	if (!split) { // no split, that means that the whole expression is in brackets
		return calc(expr.substr(1, expr.size() - 2));
	}
	int left = calc(expr.substr(0, split));
	int right = calc(expr.substr(split + 1, expr.size() - split));

	return apply(expr[split], left, right);
}

int main() {
    cout << calc("123") << endl;
    cout << calc("12+123") << endl;
    cout << calc("(1+2)*3") << endl;
    cout << calc("((3*4)+5)") << endl;
    cout << calc("(2+3+4*5)+5*6") << endl;
}
