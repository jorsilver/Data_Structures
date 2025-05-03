#ifndef SORTING_H
#define SORTING_H

#include <iostream>

using namespace std;

//Print an array given a pointer and its size
void print(double* arr, int size){
    for (int i = 0; i < size; i++){
        cout << arr[i] << ", ";
    }
    cout << endl;
}

//Swap two elements
void swap(double& a, double& b){
    double temp = a;
    a = b;
    b = temp;
}

//Bubble Sort
void bubbleSort(double* arr, int size){
    for (int i = 0; i < size - 1; ++i){
        for (int j = 0; j < size - i - 1; ++j){
            if (arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
        }
    }
}

//Insertion Sort
void insertionSort(double* arr, int size){
    for (int i = 1; i < size; ++i){
        int j = i;
        while (j > 0 && arr[j] < arr[j-1]){
            swap(arr[j], arr[j-1]);
            --j;
        }
    }
}

//Selection Sort
void selectionSort(double* arr, int size){
    for (int i = 0; i < size - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) swap(arr[i], arr[min]);
    }
}

//Partition
int partition(double* arr, int low, int high){
    double pivot = arr[high];
    int i = low;
    for (int j = low; j < high; ++j){
        if (arr[j] < pivot) swap(arr[i++], arr[j]);
    }
    swap(arr[i], arr[high]);
    return i;
}

//Quick Sort
void quickSort(double* arr, int low, int high){
    if (low < high){
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

//Merge
void merge(double* arr, int low, int mid, int high){
    int mergedSize = high - low + 1;
    double mergedNumbers[mergedSize];
    int mergePos = 0, leftPos = low, rightPos = mid + 1;
    while (leftPos <= mid && rightPos <= high){
        if (arr[leftPos] <= arr[rightPos]){
            mergedNumbers[mergePos++] = arr[leftPos++];
        } else {
            mergedNumbers[mergePos++] = arr[rightPos++];
        }
    }
    while (leftPos <= mid){
        mergedNumbers[mergePos++] = arr[leftPos++];
    }
    while (rightPos <= high){
        mergedNumbers[mergePos++] = arr[rightPos++];
    }
    for (mergePos = 0; mergePos < mergedSize; ++mergePos){
        arr[low + mergePos] = mergedNumbers[mergePos];
    }
}

//Merge Sort
void mergeSort(double* arr, int low, int high){
    if (low < high){
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

#endif