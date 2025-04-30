#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm> // make_heap i sort_heap
#include <cmath>
#include <stdlib.h>

using namespace std;

template<typename T>
void InsertionSort(T arr[], int left, int right) { // Sortowanie przez wstawianie dla małych przedziałów
    for (int i = left + 1; i <= right; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {// Przesuwanie elementów większych od pivota
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void partSort(int arr[], int N, int a, int b)
{
    int l = min(a, b);
    int r = max(a, b);

    int *temp = new int[r - l + 1];
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
int Podzial(T arr[], int low, int high) {
    T pivot = arr[high];
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
int Mediana(T arr[], int low, int mid, int high) {// Wybór mediany z trzech elementów
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
void ZastosujIntro(T arr[], int low, int high, int depthLimit) {
    int size = high - low + 1;

    if (size < 16) {
        InsertionSort(arr, low, high);
        return;
    }

    if (depthLimit == 0) {
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
    int* tab500000 = new int[500000]; //bez dynamicznej nie działało
    int* tab1000000 = new int[1000000]; //bez dynamicznej nie działało

    fstream Wyniki;
    Wyniki.open("WynikiIntro99_7.csv", ios::out | ios::app);
    Wyniki << "100,500,1000,5000,10000,50000,100000,500000,1000000" << endl;

    for (int i = 0; i < 100; i++) {
		GenerateRandomArray<int>(tab100, 100, 1, 1000000); // Generowanie tablicy 100 elementów z wartościami z przedziału
        partSort(tab100, 100, 0, 99); // Sortowanie 25 elementów
		auto begin = chrono::steady_clock::now();// początek pomiaru czasu
		IntroSort<int>(tab100, 100); // Sortowanie
		auto end = chrono::steady_clock::now(); // koniec pomiaru czasu
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ","; //zapis do pliku
		cout << "Wyniki dla 100 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        GenerateRandomArray<int>(tab500, 500, 1, 1000000);
        partSort(tab500, 500, 0, 498);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab500, 500);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << "Wyniki dla 500 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        GenerateRandomArray<int>(tab1000, 1000, 1, 1000000);
        partSort(tab1000, 1000, 0, 997);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab1000, 1000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << "Wyniki dla 1000 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        GenerateRandomArray<int>(tab5000, 5000, 1, 1000000);
        partSort(tab5000, 5000, 0, 4985);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab5000, 5000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << "Wyniki dla 5000 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        GenerateRandomArray<int>(tab10000, 10000, 1, 1000000);
        partSort(tab10000, 10000, 0, 9970);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab10000, 10000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << "Wyniki dla 10000 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        GenerateRandomArray<int>(tab50000, 50000, 1, 1000000);
        partSort(tab50000, 50000, 0, 49850);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab50000, 50000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << "Wyniki dla 50000 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        GenerateRandomArray<int>(tab100000, 100000, 1, 1000000);
        partSort(tab100000, 100000, 0, 99700);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab100000, 100000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << "Wyniki dla 100000 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        GenerateRandomArray<int>(tab500000, 500000, 1, 1000000);
		partSort(tab500000, 500000, 0, 498500);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab500000, 500000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << ",";
		cout << "Wyniki dla 500000 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;

        GenerateRandomArray<int>(tab1000000, 1000000, 1, 1000000);
		partSort(tab1000000, 1000000, 0, 997000);
        begin = chrono::steady_clock::now();
        IntroSort<int>(tab1000000, 1000000);
        end = chrono::steady_clock::now();
        Wyniki << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
		cout << "Wyniki dla 1000000 elementów: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << endl;
    }
    return 0;
}