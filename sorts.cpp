#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

void print(int* x, int length) {
    for (int i = 0; i < length; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

template <typename T>
void swap(T* a, T* b) {
    T c = *a;
    *a = *b;
    *b = c;
    return;
}

void bubbleSort(int* x, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1; j++) {
            if (x[j] > x[j + 1]) {
                swap(&x[j], &x[j + 1]);
            }
        }
    }
    return;
}

void insertionSort(int* x, int length) {
    for (int i = length - 1; i > 0; i--) {
        if (x[i] < x[i - 1]) swap(&x[i], &x[i - 1]);
    }
    int tmp, j;
    for (int i = 2; i < length; i++) {
        tmp = x[i];
        j = i;
        while (x[j - 1] > tmp) {
            x[j] = x[j - 1]; 
            j--;
        }
        x[j] = tmp;
    }
    return;
}

void selectionSort(int* x, int length) {
    int min_i;
    for (int i = 0; i < length - 1; i++) {
        min_i = i;
        for (int j = i + 1; j < length; j++) {
            if (x[j] < x[min_i]) min_i = j;
        }
        swap(&x[i], &x[min_i]);
    }
    return;
}

void shellSort(int* x, int length) {
    int j, tmp; 
    for (int h = length / 2; h > 0; h /= 2) {
        for (int i = h; i < length; i++) {
            j = i;
            tmp = x[i];
            while (j >= h && x[j - h] > tmp) {
                x[j] = x[j - h];
                j -= h;
            }
            x[j] = tmp;
        }
    }
    return;
}

void merge(int* x, int l, int mid, int r) {
    int* y = new int[r - l], a = l, b = mid, c = 0;
    while (c < r - l) {
        if (b < r && a < mid) {
            if (x[a] < x[b]) {
                y[c] = x[a];
                x[a] = y[a - l];
                a++; 
            } else {
                y[c] = x[b];
                b++;
            }
            c++;
        } else {
            while (a < mid) {
                y[c] = x[a];
                x[a] = y[a - l];
                a++;
                c++;
            }
            while (b < r) {
                y[c] = x[b];
                x[a] = y[a - l];
                a++;
                b++;
                c++;
            }
            while (a < r) {
                x[a] = y[a - l];
                a++;
            }
        }
    }
}

void mergeSort(int* x, int l, int r) {
    if (r - l == 1) return;
    int mid = (l + r) / 2;
    mergeSort(x, l, mid);
    mergeSort(x, mid, r);
    merge(x, l, mid, r);
}

void merge2(int* x, int l, int mid, int r, int* y) {
    int a = l, b = mid, i = l;
    while (i < r) {
        if (a < mid && b < r) {
            if (x[a] < x[b]) {
                y[i] = x[a];
                x[a] = y[a];
                a++;
            } else {
                y[i] = x[b];
                b++;
            }
            i++;
        } else {
            while (a < mid) {
                y[i] = x[a];
                x[a] = y[a];
                a++;
                i++;
            }
            while (a < b) {
                x[a] = y[a];
                a++;
            }
            i = r;
        }
    }
}

void mergeSort2(int* x, int l, int r, int* y = nullptr) {
    if (r - l == 1) {
        y[r] = x[r];
        return;
    }
    if (y == nullptr) {
        y = new int[r];
    }
    int mid = (l + r) / 2;
    mergeSort2(x, l, mid, y);
    mergeSort2(x, mid, r, y);
    merge2(x, l, mid, r, y);
}

void quickSort(int* x, int l, int r, int length) {
    if (l >= r) return;
    int pivot = x[(r + l) / 2];
    int a = l, b = r;
    while (a <= b) {
        while (x[a] < pivot) a++;
        while (x[b] > pivot) b--;
        if (a <= b) {
            swap(&x[a], &x[b]);
            //print(x, length);
            a++;
            b--;
        }
    }
    //cout << endl;
    quickSort(x, l, b, length);
    quickSort(x, a, r, length);
}

void countSort(int* x, int length) {
    
}

int kStatistics(int* x, int length, int k) {
    srand(time(NULL));
    int tmp = x[rand() % length];
    int *l = new int[length], lengthL = 0, *v = new int[length], lengthV = 0, *r = new int[length], lengthR = 0;
    for(int i = 0; i < length; i++) {
        if (x[i] < tmp) {
            l[lengthL] = x[i];
            lengthL++;
        } else if (x[i] == tmp) {
            v[lengthV] = tmp;
            lengthV++;
        } else {
            r[lengthR] = x[i];
            lengthR++;
        }
    }
    if (k <= lengthL) {
        delete[] v;
        delete[] r;
        return kStatistics(l, lengthL, k);
    } else if (k <= lengthL + lengthV) {
        delete[] v;
        delete[] r;
        delete[] l;
        return tmp;
    } else {
        delete[] l;
        delete[] v;
        return kStatistics(r, lengthR, k - lengthL - lengthV);
    }
}

int main() {
    srand(time(NULL));
    int n, k;
    int* arr;
    cout << "Enter length of array ";
    cin >> n;
    arr = new int[n];
    cout << "Enter mode of array initializing (r - random, w - input) ";
    char m;
    cin >> m;
    if (m == 'r') {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10;
            cout << arr[i] << " ";
        }
    } else {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }
    cout << "\nEnter kth statistics for searching ";
    cin >> k;
    cout << "kth statistics = " << kStatistics(arr, n, k) << endl;
    quickSort(arr, 0, n - 1, n);
    cout << endl << "Sorted array: \n";
    print(arr, n);
    return 0;
}