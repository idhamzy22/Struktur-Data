#include <iostream>

using namespace std;

void displayArray(int *arr, int size) {
    cout << "Nilai dalam array: ";
    for(int i = 0; i < size; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int calculateTotal(int *arr, int size) {
    int total = 0;
    for(int i = 0; i < size; i++) {
        total += *(arr + i);
    }
    return total;
}

int findMax(int *arr, int size) {
    int max = *arr;
    for(int i = 1; i < size; i++) {
        if (*(arr + i) > max) {
            max = *(arr + i);
        }
    }
    return max;
}

int findMin(int *arr, int size) {
    int min = *arr;
    for(int i = 1; i < size; i++) {
        if (*(arr + i) < min) {
            min = *(arr + i);
        }
    }
    return min;
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortArray(int *arr, int size, bool ascending) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (ascending) {
                if (*(arr + j) > *(arr + j + 1)) {
                    swap(arr + j, arr + j + 1);
                }
            } else {
                if (*(arr + j) < *(arr + j + 1)) {
                    swap(arr + j, arr + j + 1);
                }
            }
        }
    }
}

int main() {
    const int SIZE = 5;
    int arr[SIZE] = {5, 2, 7, 1, 9};

    displayArray(arr, SIZE);

    cout << "Total nilai dalam array: " << calculateTotal(arr, SIZE) << endl;

    cout << "Nilai maksimum dalam array: " << findMax(arr, SIZE) << endl;

    cout << "Nilai minimum dalam array: " << findMin(arr, SIZE) << endl;

    sortArray(arr, SIZE, true);
    cout << "Array setelah diurutkan secara ascending: ";
    displayArray(arr, SIZE);

    sortArray(arr, SIZE, false);
    cout << "Array setelah diurutkan secara descending: ";
    displayArray(arr, SIZE);

    return 0;
}