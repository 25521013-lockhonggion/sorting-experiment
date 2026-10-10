#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
using namespace std;

const string FOLDER = "C:\\sorting_data\\";

vector<double> docFile(const string& path) {
    ifstream in(path);
    int n = 0;
    in >> n;
    vector<double> a(n);
    for (int i = 0; i < n; i++) in >> a[i];
    return a;
}

bool daSapXep(const vector<double>& a) {
    for (size_t i = 1; i < a.size(); i++)
        if (a[i - 1] > a[i]) return false;
    return true;
}

int main() {
    double tong = 0;
    for (int k = 1; k <= 10; k++) {
        string name = FOLDER + "data_" + (k < 10 ? "0" : "") + to_string(k) + ".txt";
        vector<double> a = docFile(name);
        if (a.empty()) { cout << "Khong doc duoc " << name << endl; return 1; }

        auto t1 = chrono::steady_clock::now();
        sort(a.begin(), a.end());               // hàm sort có sẵn của C++
        auto t2 = chrono::steady_clock::now();

        double ms = chrono::duration<double, milli>(t2 - t1).count();
        tong += ms;
        cout << "Day " << k << ": " << ms << " ms" << (daSapXep(a) ? "" : "  (KET QUA SAI!)") << endl;
    }
    cout << "Trung binh: " << tong / 10 << " ms" << endl;
    return 0;
}