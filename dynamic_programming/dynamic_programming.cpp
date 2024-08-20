#include <iostream> // Incluye la librería estándar de entrada y salida
#include <vector> // Incluye la librería estándar de vectores

using namespace std; // Permite usar los elementos del espacio de nombres std sin tener que prefixarlos con std::

/**
 * Función que calcula el n-ésimo número de Fibonacci utilizando programación dinámica.
 * @param n El índice del número de Fibonacci a calcular.
 * @return El n-ésimo número de Fibonacci.
 */
int fibonacci(int n) {
    vector<int> fib(n + 1, 0); // Crea un vector de tamaño n+1 inicializado con ceros
    fib[0] = 0; // Inicializa el primer número de Fibonacci
    fib[1] = 1; // Inicializa el segundo número de Fibonacci
    for (int i = 2; i <= n; ++i) { // Itera desde 2 hasta n
        fib[i] = fib[i - 1] + fib[i - 2]; // Calcula el i-ésimo número de Fibonacci sumando los dos anteriores
    }
    return fib[n]; // Devuelve el n-ésimo número de Fibonacci
}

/**
 * Función principal del programa.
 * Solicita al usuario un número n y calcula el n-ésimo número de Fibonacci.
 * @return 0 si la ejecución es exitosa.
 */
int main() {
    int n; // Declara una variable n para almacenar el número de Fibonacci a calcular
    cout << "Introduce el número n para calcular el n-ésimo número de Fibonacci: "; // Solicita al usuario que introduzca un número
    cin >> n; // Lee el número introducido por el usuario
    int result = fibonacci(n); // Llama a la función fibonacci y almacena el resultado en result
    cout << "El " << n << "-ésimo número de Fibonacci es: " << result << endl; // Imprime el resultado
    return 0; // Finaliza la ejecución del programa
}

//g++ -o dynamic_programming dynamic_programming.cpp
//./dynamic_programming