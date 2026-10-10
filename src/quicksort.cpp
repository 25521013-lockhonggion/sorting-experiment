#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

const string FOLDER = "C:\\sorting_data\\";

// Đọc 1 file dữ liệu: dòng đầu là n, sau đó là n số thực
vector<double> docFile(const string& path) {
    ifstream in(path);
    int n = 0;
    in >> n;
    vector<double> a(n);
    for (int i = 0; i < n; i++) in >> a[i];
    return a;
}

// Kiểm tra dãy đã tăng dần chưa
bool daSapXep(const vector<double>& a) {
    for (size_t i = 1; i < a.size(); i++)
        if (a[i - 1] > a[i]) return false;
    return true;
}

mt19937 rng(12345);   // dùng để chọn pivot ngẫu nhiên

void quickSort(vector<double>& a, int left, int right) {
    if (left >= right) return;
    // chọn pivot ngẫu nhiên (để dãy đã sắp xếp không bị chậm)
    double pivot = a[left + rng() % (right - left + 1)];
    int i = left, j = right;
    while (i <= j) {
        while (a[i] < pivot) i++;      // tìm phần tử bên trái >= pivot
        while (a[j] > pivot) j--;      // tìm phần tử bên phải <= pivot
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    quickSort(a, left, j);             // sắp xếp nửa trái
    quickSort(a, i, right);            // sắp xếp nửa phải
}

int main() {
    double tong = 0;
    for (int k = 1; k <= 10; k++) {
        string name = FOLDER + "data_" + (k < 10 ? "0" : "") + to_string(k) + ".txt";
        vector<double> a = docFile(name);
        if (a.empty()) { cout << "Khong doc duoc " << name << endl; return 1; }

        auto t1 = chrono::steady_clock::now();
        quickSort(a, 0, (int)a.size() - 1);
        auto t2 = chrono::steady_clock::now();

        double ms = chrono::duration<double, milli>(t2 - t1).count();
        tong += ms;
        cout << "Day " << k << ": " << ms << " ms" << (daSapXep(a) ? "" : "  (KET QUA SAI!)") << endl;
    }
    cout << "Trung binh: " << tong / 10 << " ms" << endl;
    return 0;
}