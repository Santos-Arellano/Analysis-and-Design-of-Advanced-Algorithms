#include <iostream>  // Incluye la librería para manejar entradas y salidas (como imprimir en pantalla)
#include <vector>    // Incluye la librería para utilizar vectores, que son arreglos dinámicos en C++

// Función para combinar dos subarreglos que ya están ordenados en un solo arreglo ordenado
void merge(std::vector<int>& arr, int left, int mid, int right) {
    // Calcula el tamaño de los dos subarreglos
    int n1 = mid - left + 1;  // Tamaño del primer subarreglo
    int n2 = right - mid;     // Tamaño del segundo subarreglo

    // Crea arreglos temporales para almacenar los elementos de cada subarreglo
    std::vector<int> L(n1), R(n2);

    // Copia los datos del arreglo original a los subarreglos temporales L[] y R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];  // Llena el arreglo L[] con la primera mitad
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];  // Llena el arreglo R[] con la segunda mitad

    // Inicializa los índices para recorrer L[], R[] y el arreglo original arr[]
    int i = 0, j = 0, k = left;

    // Combina los subarreglos L[] y R[] de nuevo en arr[]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {  // Compara los elementos y coloca el menor en arr[]
            arr[k] = L[i];
            ++i;  // Avanza en L[] si se usó su elemento
        } else {
            arr[k] = R[j];
            ++j;  // Avanza en R[] si se usó su elemento
        }
        ++k;  // Avanza en arr[] después de colocar un elemento
    }

    // Copia los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Copia los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Función recursiva para ordenar el arreglo utilizando el algoritmo Merge Sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {  // Verifica que haya más de un elemento a ordenar
        // Encuentra el punto medio del arreglo para dividirlo en dos mitades
        int mid = left + (right - left) / 2;

        // Ordena recursivamente la primera mitad
        mergeSort(arr, left, mid);
        // Ordena recursivamente la segunda mitad
        mergeSort(arr, mid + 1, right);

        // Combina las dos mitades ordenadas en un solo arreglo
        merge(arr, left, mid, right);
    }
}

int main() {
    // Crea un arreglo de ejemplo para ordenar
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);  // Calcula el tamaño del arreglo

    // Convierte el arreglo a un vector (un tipo de dato más flexible en C++)
    std::vector<int> vec(arr, arr + arr_size);

    // Imprime el arreglo original antes de ordenarlo
    std::cout << "Arreglo original: ";
    for (int i = 0; i < arr_size; ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    // Llama a la función mergeSort para ordenar el arreglo
    mergeSort(vec, 0, arr_size - 1);

    // Imprime el arreglo ya ordenado
    std::cout << "Arreglo ordenado: ";
    for (int i = 0; i < arr_size; ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    return 0;  // Termina el programa
}


// g++ -o main MergeSort.cpp 
// ./main