#include <iostream>
#include <cstdio>

using namespace std;

int X = 100, Y = 50, Z = 30;

struct aquarium {
    int x, y, z;

    aquarium(int x, int y, int z) : x(x), y(y), z(z) {
    }

    int volume() {
        return x * y * z;
    }

    bool isfull(int water) {
        return volume() <= water;
    }

    double depth(int water) {
        return double(water) / (x * y);
    }
};

int main() {
    int b, h;
    cin >> b >> h;
    int f, a;
    cin >> f >> a;

    aquarium first = aquarium(b, h, Z);
    aquarium second = aquarium(X - b, h, Z);
    aquarium total = aquarium(X, Y, Z);

    bool swapped = false;
    if (f > b) {
        swapped = true;
        swap(first, second);
    }

    int l;
    cin >> l;

    for (int i = 0; i < l; i++) {
        int p, t;
        cin >> p >> t;

        int volume = t * a;

        int firstVolume = first.isfull(volume) ? first.volume() : volume;
        volume -= firstVolume;
        int secondVolume = second.isfull(volume) ? second.volume() : volume;
        volume -= secondVolume;

        cout << firstVolume << " " << secondVolume << " " << volume << endl;

        double result = 0.0;
        if (volume > 0) {
            result = total.isfull(t * a) ? Y : total.depth(t * a);
        } else {
            if (p < b) {
                result = swapped ? second.depth(secondVolume) : first.depth(firstVolume);
            } else {
                result = swapped ? first.depth(firstVolume) : second.depth(secondVolume);
            }
        }

        printf("%.03f\n", result);
    }
}
