#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long n;
    cin >> n;

    int count = 0;
    while (n > 0) {
        int k = floor(pow(n, 1.0/3.0));
        if (k == 0) {
            break;
        }
        n -= k * k * k;
        count++;
    }
    cout << count << endl;
}
