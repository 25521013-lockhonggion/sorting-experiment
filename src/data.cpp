#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

// Thư mục lưu dữ liệu (nhớ tạo sẵn thư mục này, nhớ có dấu \\ ở cuối)
const string FOLDER = "C:\\sorting_data\\";

    int main() {
    const int N = 1000000;                      // số phần tử mỗi dãy
    mt19937_64 rng(12345);                      // bộ sinh số ngẫu nhiên, seed cố định
    uniform_real_distribution<double> dist(-1000000.0, 1000000.0);

    for (int k = 1; k <= 10; k++) {
        vector<double> a(N);
        for (int i = 0; i < N; i++) a[i] = dist(rng);   // sinh số ngẫu nhiên

        if (k == 1) sort(a.begin(), a.end());                    // dãy 1: tăng dần
        if (k == 2) sort(a.begin(), a.end(), greater<double>()); // dãy 2: giảm dần

        string name = FOLDER + "data_" + (k < 10 ? "0" : "") + to_string(k) + ".txt";
        ofstream out(name);
        if (!out) { cout << "Khong tao duoc file: " << name << endl; return 1; }
        out << N << "\n" << fixed << setprecision(6);
        for (int i = 0; i < N; i++) out << a[i] << "\n";
        out.close();
        cout << "Da tao " << name << endl;
    }
    return 0;
}   