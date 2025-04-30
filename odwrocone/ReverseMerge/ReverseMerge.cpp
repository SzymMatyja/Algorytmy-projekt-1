#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

template<typename T>
void merge(T* tab, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T* L = new T[n1]; 	// stworzenie tymczasowych tablic
    T* R = new T[n2];

    for (int i = 0; i < n1; i++) 	// kopiowanie danych do tymczasowych tablic L[] i R[]
        L[i] = tab[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = tab[mid + 1 + j];

    int i = 0, j = 0, k = left; // scal L[] i R[] do tab[]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            tab[k] = L[i];
            i++;
        }
        else {
            tab[k] = R[j];
            j++;
        }
        k++;
    }

    //  jeśli są kopiuj pozostałe elementy L[]
    while (i < n1) {
        tab[k] = L[i];
        i++;
        k++;
    }

    //  jeśli są kopiuj pozostałe elementy R[]
    while (j < n2) {
        tab[k] = R[j];
        j++;
        k++;
    }

    // uwalnia pamięć
    delete[] L;
    delete[] R;
}

template<typename T>
void MergeSort(T* tab, int size) { // sortowanie przez scalanie
    for (int current_size = 1; current_size < size; current_size *= 2) {
        for (int left_start = 0; left_start < size - 1; left_start += 2 * current_size) {
            int mid = std::min(left_start + current_size - 1, size - 1);
            int right_end = std::min(left_start + 2 * current_size - 1, size - 1);
            merge<T>(tab, left_start, mid, right_end);
        }
    }
}

template<typename T>
void GenerateArray(T* tab, int size) {
    for (int i = 0; i < size; ++i) {
        tab[i] = size - i;
    }
}

int tab100[100];
int tab500[500];
int tab1000[1000];
int tab5000[5000];
int tab10000[10000];
int tab50000[50000];
int tab100000[100000];
int tab500000[500000];
int tab1000000[1000000]; // wielkości tablicy do testów

fstream Wyniki;

int main() {
    Wyniki.open("ReverseMerge.csv", ios::out | ios::app);
    Wyniki << "100,500,1000,5000,10000,50000,100000,500000,1000000," << endl;

    for (int i = 0; i < 100; i++) {
        GenerateArray<int>(tab100, 100); //100
        auto begin = chrono::steady_clock::now();
        MergeSort<int>(tab100, 100);
        auto end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab500, 500); //500
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab500, 500);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab1000, 1000); //1000
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab1000, 1000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab5000, 5000); //5000
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab5000, 5000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab10000, 10000); //10000
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab10000, 10000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab50000, 50000); //50000
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab50000, 50000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab100000, 100000); //100000
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab100000, 100000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab500000, 500000); //500000
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab500000, 500000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab1000000, 1000000); //1000000
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab1000000, 1000000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
    }
    return 0;
}