#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm> // make_heap i sort_heap
#include <cmath> 

using namespace std;

template<typename T>
void Zamien(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<typename T>
void InsertionSort(T arr[], int left, int right) { // Sortowanie przez wstawianie dla małych przedziałów
    for (int i = left + 1; i <= right; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) { // Przesuwanie elementów większych od pivota
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template<typename T>
int Podzial(T arr[], int low, int high) {
    T pivot = arr[high]; // Wybór pivota
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

template<typename T>
int Mediana(T arr[], int low, int mid, int high) { // Wybór mediany z trzech elementów
    if (arr[low] < arr[mid]) {
        if (arr[mid] < arr[high])
            return mid;
        else if (arr[low] < arr[high])
            return high;
        else
            return low;
    }
    else {
        if (arr[low] < arr[high])
            return low;
        else if (arr[mid] < arr[high])
            return high;
        else
            return mid;
    }
}

template<typename T>
void ZastosujIntro(T arr[], int low, int high, int depthLimit) { // Główna funkcja Introsorta

    int size = high - low + 1;

    if (size < 16) { // Dla małych partycji
        InsertionSort(arr, low, high);
        return;
    }

    if (depthLimit == 0) { // Jeśli osiągnięto limit = kopcowanie
        make_heap(arr + low, arr + high + 1);
        sort_heap(arr + low, arr + high + 1);
        return;
    }

    int mid = low + (high - low) / 2;
    int pivot_index = Mediana(arr, low, mid, high);

    swap(arr[pivot_index], arr[high]);

    int partitionPoint = Podzial(arr, low, high);

    ZastosujIntro(arr, low, partitionPoint - 1, depthLimit - 1);
    ZastosujIntro(arr, partitionPoint + 1, high, depthLimit - 1);
}

template<typename T>
void IntroSort(T arr[], int size) {
    int depthLimit = 2 * log2(size);
    ZastosujIntro(arr, 0, size - 1, depthLimit);
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

int main() {
    int tab100[100];
    int tab500[500];
    int tab1000[1000];
    int tab5000[5000];
    int tab10000[10000];
    int tab50000[50000];
    int tab100000[100000];
	int* tab500000 = new int[500000]; //bez dynamicznej mi nie działało
    int* tab1000000 = new int[1000000]; //bez dynamicznej nie działało

    fstream Wyniki;
    Wyniki.open("WynikiIntro.csv", ios::out | ios::app);
    Wyniki << "100,500,1000,5000,10000,50000,100000,500000,1000000" << endl;

    for (int i = 0; i < 100; i++) {
        GenerateRandomArray<int>(tab100, 100, 1, 1000000);
        auto begin = chrono::steady_clock::now();
        IntroSort<int>(tab100, 100);
        auto end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab500, 500, 1, 1000000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab500, 500);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab1000, 1000, 1, 1000000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab1000, 1000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab5000, 5000, 1, 1000000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab5000, 5000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab10000, 10000, 1, 1000000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab10000, 10000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab50000, 50000, 1, 1000000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab50000, 50000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab100000, 100000, 1, 1000000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab100000, 100000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab500000, 500000, 1, 1000000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab500000, 500000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";

        GenerateRandomArray<int>(tab1000000, 1000000, 1, 1000000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab1000000, 1000000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
    }
    return 0;
}