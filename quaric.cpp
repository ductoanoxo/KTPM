#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

int solveQuartic(double a, double b, double c, double x[]) {
    if (a == 0 && b == 0 && c == 0) {
        return -1; // vô số nghiệm
    }
    if (a == 0 && b == 0) {
        return 0; // vô nghiệm
    }
    if (a == 0) { // phương trình b*y + c = 0
        double y = -c / b;
        if (y < 0) return 0;
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }

    double delta = b * b - 4 * a * c;
    if (delta < 0) return 0;

    double y1 = (-b + sqrt(delta)) / (2 * a);
    double y2 = (-b - sqrt(delta)) / (2 * a);

    int count = 0;
    if (y1 >= 0) {
        x[count++] = sqrt(y1);
        x[count++] = -sqrt(y1);
    }
    if (y2 >= 0 && y2 != y1) {
        x[count++] = sqrt(y2);
        x[count++] = -sqrt(y2);
    }
    return count;
}

bool checkEqual(double a, double b, double eps = 1e-6) {
    return fabs(a - b) < eps;
}

void runTest(double a, double b, double c, vector<double> expected) {
    double x[4];
    int n = solveQuartic(a, b, c, x);

    if (expected.empty()) {
        // Không có nghiệm hoặc vô số nghiệm
        assert(n == 0 || n == -1);
    }
    else {
        assert(n == (int)expected.size());
        for (double e : expected) {
            bool found = false;
            for (int i = 0; i < n; i++) {
                if (checkEqual(x[i], e)) {
                    found = true; break;
                }
            }
            assert(found); // nghiệm mong đợi phải xuất hiện
        }
    }
    cout << "Test (" << a << "," << b << "," << c << ") passed.\n";
}

int main() {
    runTest(0, 0, 0, {});                   // vô số nghiệm
    runTest(0, 0, 5, {});                   // vô nghiệm
    runTest(0, 2, -8, { 2, -2 });             // x = ±2
    runTest(1, 0, 1, {});                   // vô nghiệm
    runTest(1, -5, 4, { 2, -2, 1, -1 });      // x = ±2, ±1
    runTest(1, 0, -1, { 1, -1 });             // x = ±1
    runTest(1, -2, 1, { 1, -1 });             // nghiệm kép y=1 ⇒ x=±1

    cout << "All tests passed!\n";
    return 0;
}
