#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Đọc dữ liệu từ file text
void readData(const string& filename, vector<double>& a) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Khong mo duoc file: " << filename << '\n';
        exit(1);
    }
    a.clear();
    double x;
    while (fin >> x) a.push_back(x);
}

// Ghi dữ liệu ra file text
void writeData(const string& filename, const vector<double>& a) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Khong ghi duoc file: " << filename << '\n';
        exit(1);
    }
    fout << fixed << setprecision(8);
    for (double x : a) fout << x << '\n';
}

// -------------------- QUICKSORT --------------------
void quickSort(vector<double>& a, int l, int r) {
    while (l < r) {
        int m = l + (r - l) / 2;

        // Chọn pivot theo median-of-three
        if (a[m] < a[l]) swap(a[m], a[l]);
        if (a[r] < a[l]) swap(a[r], a[l]);
        if (a[r] < a[m]) swap(a[r], a[m]);

        double pivot = a[m];
        int i = l, j = r;

        while (i <= j) {
            while (a[i] < pivot) ++i;
            while (a[j] > pivot) --j;
            if (i <= j) {
                swap(a[i], a[j]);
                ++i;
                --j;
            }
        }

        // Đệ quy phần nhỏ hơn trước, giảm độ sâu stack
        if (j - l < r - i) {
            quickSort(a, l, j);
            l = i;
        } else {
            quickSort(a, i, r);
            r = j;
        }
    }
}

// -------------------- HEAPSORT --------------------
void heapify(vector<double>& a, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<double>& a) {
    int n = (int)a.size();

    // Xây dựng max-heap
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(a, n, i);

    // Lần lượt đưa phần tử lớn nhất về cuối
    for (int i = n - 1; i > 0; --i) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// -------------------- MERGESORT --------------------
void mergeSort(vector<double>& a, vector<double>& tmp, int l, int r) {
    if (l >= r) return;

    int m = l + (r - l) / 2;
    mergeSort(a, tmp, l, m);
    mergeSort(a, tmp, m + 1, r);

    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i <= m) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];

    for (i = l; i <= r; ++i) a[i] = tmp[i];
}

// -------------------- MAIN --------------------
int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <algorithm> <input.txt> <output.txt>\n";
        cerr << "algorithm: quick | heap | merge | std\n";
        return 1;
    }

    string algo = argv[1];
    string inFile = argv[2];
    string outFile = argv[3];

    vector<double> a;
    readData(inFile, a);

    cout << "Da doc " << a.size() << " so tu " << inFile << '\n';

    if (algo == "quick") {
        quickSort(a, 0, (int)a.size() - 1);
    } else if (algo == "heap") {
        heapSort(a);
    } else if (algo == "merge") {
        vector<double> tmp(a.size());
        mergeSort(a, tmp, 0, (int)a.size() - 1);
    } else if (algo == "std") {
        sort(a.begin(), a.end());
    } else {
        cerr << "Thuat toan khong hop le: " << algo << '\n';
        return 1;
    }

    writeData(outFile, a);
    cout << "Da ghi ket qua vao " << outFile << '\n';
    return 0;
}
