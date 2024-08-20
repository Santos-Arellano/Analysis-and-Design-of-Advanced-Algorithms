// Merge sort
// The program receives an integer N, followed by N real values ​​(double, one on each line) through standard input.
// The output of the program is a list of the N values ​​ordered from Highest to Lowest
// Complejidad del algoritmo Merge Sort: O(n log n)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función para combinar dos subvectores ordenados
void merge(vector<double> &arr, int l, int m, int r) {
    // Calcula el tamaño de los subvectores
    int n1 = m - l + 1;
    int n2 = r - m;
    // Crea vectores temporales
    vector<double> L(n1), R(n2);
    // Copia los datos a los vectores temporales L[] y R[]
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    // Indices iniciales de los subvectores y del vector combinado
    int i = 0;
    int j = 0;
    int k = l;
    // Combina los vectores temporales de nuevo en arr[l..r]
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) { // Ordena de Mayor a Menor
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copia los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copia los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función recursiva para ordenar el vector usando Merge Sort
void mergeSort(vector<double> &arr, int l, int r) {
    // Si el índice izquierdo es mayor o igual al derecho, la función retorna (caso base)
    if (l >= r) {
        return;
    }
    // Encuentra el punto medio del vector
    int m = l + (r - l) / 2;
    // Llama recursivamente a mergeSort para la primera mitad
    mergeSort(arr, l, m);
    // Llama recursivamente a mergeSort para la segunda mitad
    mergeSort(arr, m + 1, r);
    // Combina las dos mitades ordenadas
    merge(arr, l, m, r);
}

// Función para imprimir el vector
void printVector(const vector<double>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        if (i != 0) {
            cout << ", ";
        }
        cout << arr[i];
    }
    cout << endl;
}

int main() {
    int n;
    // Solicita al usuario el número de elementos
    cout << "Enter the number of elements: ";
    cin >> n;

    // Crea un vector de tamaño n
    vector<double> arr(n);
    // Lee los elementos del vector desde la entrada estándar
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << endl;

    // Llama a la función mergeSort para ordenar el vector
    mergeSort(arr, 0, n - 1);

    // Imprime el vector ordenado
    cout << "Sorted values: ";
    printVector(arr);

    return 0;
}

//g++ -o A01637254_Act1.1 A01637254_Act1.1.cpp
//./A01637254_Act1.1