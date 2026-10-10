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

// Sắp xếp đoạn [left, right] của a; tmp là mảng phụ cùng kích thước
void mergeSort(vector<double>& a, vector<double>& tmp, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(a, tmp, left, mid);        // sắp xếp nửa trái
    mergeSort(a, tmp, mid + 1, right);   // sắp xếp nửa phải

    // trộn hai nửa đã sắp xếp vào tmp
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else              tmp[k++] = a[j++];
    }
    while (i <= mid)   tmp[k++] = a[i++];
    while (j <= right) tmp[k++] = a[j++];

    for (k = left; k <= right; k++) a[k] = tmp[k];   // chép kết quả về a
}

int main() {
    double tong = 0;
    for (int k = 1; k <= 10; k++) {
        string name = FOLDER + "data_" + (k < 10 ? "0" : "") + to_string(k) + ".txt";
        vector<double> a = docFile(name);
        if (a.empty()) { cout << "Khong doc duoc " << name << endl; return 1; }

        auto t1 = chrono::steady_clock::now();
        vector<double> tmp(a.size());
        mergeSort(a, tmp, 0, (int)a.size() - 1);
        auto t2 = chrono::steady_clock::now();

        double ms = chrono::duration<double, milli>(t2 - t1).count();
        tong += ms;
        cout << "Day " << k << ": " << ms << " ms" << (daSapXep(a) ? "" : "  (KET QUA SAI!)") << endl;
    }
    cout << "Trung binh: " << tong / 10 << " ms" << endl;
    return 0;
}