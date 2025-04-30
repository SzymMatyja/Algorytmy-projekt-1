#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

template<typename T>
int PunktPodzialu(int l, int r);// Wybiera punkt podziału dla algorytmu

template<typename T>
void Zamien(T* tab, int l, int r);// Zamienia dwa elementy w tablicy

template<typename T>
int PodzialTablic(T* tab, int l, int r);// Dzieli tablicę na dwie części

template<typename T>
void QuickSort(T* tab, int l, int r);

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
    Wyniki.open("ReverseQuick.csv", ios::out | ios::app);
    Wyniki << "100,500,1000,5000,10000,50000,100000,500000,1000000," << endl;

    for (int i = 0; i < 100; i++) {
        GenerateArray<int>(tab100, 100); //100
        auto begin = chrono::steady_clock::now();
        QuickSort<int>(tab100, 100);
        auto end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab500, 500); //500
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab500, 500);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab1000, 1000); //1000
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab1000, 1000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab5000, 5000); //5000
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab5000, 5000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab10000, 10000); //10000
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab10000, 10000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab50000, 50000); //50000
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab50000, 50000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab100000, 100000); //100000
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab100000, 100000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab500000, 500000); //500000
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab500000, 500000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateArray<int>(tab1000000, 1000000); //1000000
        begin = chrono::steady_clock::now();
        QuickSort<int>(tab1000000, 1000000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
        cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
    }
    return 0;
}