#include "Sorting.h"
#include <fstream>
#include <chrono>

using namespace std::chrono;

int main(int argc, char const *argv[]){
    ifstream fileInStream(argv[1]);
    if (!fileInStream) throw runtime_error("The input file could not be opened");

    int size;
    fileInStream >> size;

    double* arrBS = new double[size];
    double* arrIS = new double[size];
    double* arrSS = new double[size];
    double* arrMS = new double[size];
    double* arrQS = new double[size];
    
    for (int i = 0; i < size; i++) {
        fileInStream >> arrBS[i];
        arrIS[i] = arrBS[i];
        arrSS[i] = arrBS[i];
        arrMS[i] = arrBS[i];
        arrQS[i] = arrBS[i];
    }

    fileInStream.close();

    cout << "Sorting " << size << " doubles\n\n";
    //Bubble Sort
    auto startBS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    bubbleSort(arrBS, size);
    auto endBS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    cout << "Bubble Sort\nDuration: " << (endBS - startBS) << " milliseconds\n\n";
    delete[] arrBS;

    //Insertion Sort
    auto startIS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    insertionSort(arrIS, size);
    auto endIS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    cout << "Insertion Sort\nDuration: " << (endIS - startIS) << " milliseconds\n\n";
    delete[] arrIS;

    //Selection Sort
    auto startSS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    selectionSort(arrSS, size);
    auto endSS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    cout << "Selection Sort\nDuration: " << (endSS - startSS) << " milliseconds\n\n";
    delete[] arrSS;

    //Merge Sort
    auto startMS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    mergeSort(arrMS, 0, size - 1);
    auto endMS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    cout << "Merge Sort\nDuration: " << (endMS - startMS) << " milliseconds\n\n";
    delete[] arrMS;

    //Quick Sort
    auto startQS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    quickSort(arrQS, 0, size - 1);
    auto endQS = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    cout << "Quick Sort\nDuration: " << (endQS - startQS) << " milliseconds\n\n";
    delete[] arrQS;

    return 0;
}