#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <stdlib.h>

using namespace std;

template<typename T>
int PunktPodzialu(int l, int r);// Wybiera punkt podziału dla algorytmu QuickSort


template<typename T>
void Zamien(T* tab, int l, int r);// Zamienia dwa elementy w tablicy


template<typename T>
int PodzialTablic(T* tab, int l, int r);// Dzieli tablicę na dwie części

template<typename T>
void QuickSort(T* tab, int l, int r);

// Function implementations
template<typename T>
int PunktPodzialu(int l, int r) {
    return l + (r - l) / 2;
}

template<typename T>
void Zamien(T* tab, int l, int r) {
    T aux = tab[l];
    tab[l] = tab[r];
    tab[r] = aux;
}

template<typename T>
int PodzialTablic(T* tab, int l, int r) {
    int indeksPodzialu = PunktPodzialu<T>(l, r);
    T wartoscPodzialu = tab[indeksPodzialu];
    Zamien(tab, indeksPodzialu, r);

    int aktualnaPozycja = l;
    for (int i = l; i < r; i++) {
        if (tab[i] < wartoscPodzialu) {
            Zamien(tab, i, aktualnaPozycja);
            aktualnaPozycja++;
        }
    }
    Zamien(tab, aktualnaPozycja, r);
    return aktualnaPozycja;
}

template<typename T>
void QuickSort(T* tab, int l, int r) {
    if (l < r) {
        int i = PodzialTablic(tab, l, r);
        QuickSort(tab, l, i - 1);
        QuickSort(tab, i + 1, r);
    }
}

template<typename T>
void QuickSort(T* tab, int size) {
    if (size > 1) {
        QuickSort(tab, 0, size - 1);
    }
}

template<typename T>
void GenerateRandomArray(T* tab, int size, T minValue, T maxValue) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> dist(minValue, maxValue);
    for (int i = 0; i < size; ++i) {
        tab[i] = dist(gen);
    }
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
    Wyniki.open("WynikiQuick99_7.csv", ios::out | ios::app);
    Wyniki << "100,500,1000,5000,10000,50000,100000,500000,1000000," << endl;

    for (int i = 0; i < 100; i++) {
        GenerateRandomArray<int>(tab100, 100, 1, 1000000); //100
        partSort(tab100, 100, 0, 99);
        auto begin = chrono::steady_clock::now();
        QuickSort<int>(tab100, 100);
        auto end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab500, 500, 1, 1000000); //500
        partSort(tab500, 500, 0, 498);
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab500, 500);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab1000, 1000, 1, 1000000); //1000
        partSort(tab1000, 1000, 0, 997);
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab1000, 1000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab5000, 5000, 1, 1000000); //5000
        partSort(tab5000, 5000, 0, 4985);
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab5000, 5000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab10000, 10000, 1, 1000000); //10000
        partSort(tab10000, 10000, 0, 9970);
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab10000, 10000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab50000, 50000, 1, 1000000); //50000
        partSort(tab50000, 50000, 0, 49850);
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab50000, 50000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab100000, 100000, 1, 1000000); //100000
        partSort(tab100000, 100000, 0, 99700);
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab100000, 100000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab500000, 500000, 1, 1000000); //500000
        partSort(tab500000, 500000, 0, 498500);
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab500000, 500000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab1000000, 1000000, 1, 1000000); //1000000
        partSort(tab1000000, 1000000, 0, 997000);
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab1000000, 1000000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
    }
    return 0;
}