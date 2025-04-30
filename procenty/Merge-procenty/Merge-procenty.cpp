#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <stdlib.h>

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

void partSort(int arr[], int N, int a, int b)
{
    int l = min(a, b);
    int r = max(a, b);
    int* temp = new int[r - l + 1];
    int j = 0;
    for (int i = l; i <= r; i++) {
        temp[j] = arr[i];
        j++;
    }

    sort(temp, temp + r - l + 1);

    j = 0;
    for (int i = l; i <= r; i++) {
        arr[i] = temp[j];
        j++;
    }
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

template<typename T> //funkcja generująca tablicę z losowymi liczbami całkowitymi
void GenerateRandomArray(T* tab, int size, T minValue, T maxValue) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> dist(minValue, maxValue);
    for (int i = 0; i < size; ++i) {
        tab[i] = dist(gen);
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
    Wyniki.open("WynikiMerge25.csv", ios::out | ios::app);
    Wyniki << "100,500,1000,5000,10000,50000,100000,500000,1000000," << endl;

    for (int i = 0; i < 100; i++) {
        GenerateRandomArray<int>(tab100, 100, 1, 1000000); //100
        partSort(tab100, 100, 0, 25);
        auto begin = chrono::steady_clock::now();
        MergeSort<int>(tab100, 100);
        auto end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab500, 500, 1, 1000000); //500
        partSort(tab500, 500, 0, 125);
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab500, 500);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab1000, 1000, 1, 1000000); //1000
        partSort(tab1000, 1000, 0, 250);
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab1000, 1000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab5000, 5000, 1, 1000000); //5000
        partSort(tab5000, 5000, 0, 1250);
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab5000, 5000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab10000, 10000, 1, 1000000); //10000
        partSort(tab10000, 10000, 0, 2500);
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab10000, 10000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab50000, 50000, 1, 1000000); //50000
        partSort(tab50000, 50000, 0, 12500);
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab50000, 50000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab100000, 100000, 1, 1000000); //100000
        partSort(tab100000, 100000, 0, 25000);
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab100000, 100000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab500000, 500000, 1, 1000000); //500000
        partSort(tab500000, 500000, 0, 125000);
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab500000, 500000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab1000000, 1000000, 1, 1000000); //1000000
        partSort(tab1000000, 1000000, 0, 250000);
        begin = chrono::steady_clock::now();
        MergeSort<int>(tab1000000, 1000000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
		cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
    }
    return 0;
}