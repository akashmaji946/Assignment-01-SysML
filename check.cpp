#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

void compare_files(const char* file1, const char* file2, double tolerance = 0.001) {
    ifstream f1(file1);
    ifstream f2(file2);

    if (!f1.is_open() || !f2.is_open()) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line1, line2;
    int idx = 0;

    while (getline(f1, line1) && getline(f2, line2)) {
        double x = stod(line1);
        double y = stod(line2);

        if (fabs(x - y) > tolerance) {
            cout << "Difference at index " << idx << ": " << x << " vs " << y << endl;
        }
        idx++;
    }

    // if (f1.eof() != f2.eof()) {
    //     cout << "Files have different number of lines." << endl;
    // }

    f1.close();
    f2.close();
}

int main() {
    compare_files("OUTPUT.txt", "OUTPUT2.txt");
    return 0;
}