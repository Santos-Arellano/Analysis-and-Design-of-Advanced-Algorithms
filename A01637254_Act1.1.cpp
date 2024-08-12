// make an algorithm with merge sort with the following instructions
// The program receives an integer N, followed by N real values ​​(double, one on each line) through standard input.
// The output of the program is a list of the N values ​​ordered from Highest to Lowest

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void mergeSort(vector<double> &arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void merge(vector<double> &arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<double> L(n1), R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}



void printVector(vector<double>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << ", ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<double> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    mergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << endl;
    }
    return 0;
}

