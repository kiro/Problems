#include <iostream>
#include <vector>

using namespace std;

class interval {
	public:
		const int from, to;

		interval(int from, int to) : from(from), to(to) {
		}

		bool contains(int point) {
			return from <= point && to >= point;
		}

		bool contains(interval other) {
			return from <= other.from && to >= other.to;
		}

		bool intersects(interval other) {
			return other.from <= to && other.to >= from;
		}

		int exists() {
			return to >= from;
		}

		interval left() {
			// invalidate the interval if it has only element, so that we don't go into cycle.
			return interval(from, (from + to) / 2 + (from == to ? -1 : 0));
		}

		interval right() {
			return interval((from + to) / 2 + 1, to);
		}
};

class index_tree {
	private:
		int n;
		vector<int> elements;

		void set(int el, int index, int diff, interval i) {
			if (i.exists() && i.contains(index))  {
				elements[el] += diff;
                set(el * 2 + 1, index, diff, i.left());
                set(el * 2 + 2, index, diff, i.right());
			}
		}

		int sum(interval i, interval current, int el) {
			if (current.exists() && current.intersects(i)) {
                if (i.contains(current)) {
					return elements[el];
				}

                return sum(i, current.left(), el * 2 + 1) +
                       sum(i, current.right(), el * 2 + 2);
			}
			return 0;
		}

		int build(int el, interval i, int* arr) {
			if (i.from == i.to) {
				return elements[el] = arr[i.from];
			} else {
				return elements[el] = build(el * 2 + 1, i.left(), arr) +
				                      build(el * 2 + 2, i.right(), arr);
			}
		}
	public:
		index_tree(int n) : n(n) {
			elements = vector<int>(3 * n);
		}

		void init(int* arr) {
			build(0, interval(0, n), arr);
		}

		void set(int index, int value) {
			set(0, index, value, interval(0, n));
		}

		int sum(interval i) {
			return sum(i, interval(0, n), 0);
		}
};

int exp(int n) {
  cout << n << endl;
  return n == 1 ? 1 : 1 + exp(exp(n-1));
}

int main() {
    exp(5);
}
