#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Función para encontrar el cambio utilizando programación dinámica
vector<int> cambioDinamico(const vector<int>& denominaciones, int cambio) {
    int n = denominaciones.size();
    vector<int> dp(cambio + 1, INT_MAX);
    vector<int> monedas(cambio + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= cambio; ++i) {
        for (int j = 0; j < n; ++j) {
            if (denominaciones[j] <= i && dp[i - denominaciones[j]] != INT_MAX) {
                if (dp[i] > dp[i - denominaciones[j]] + 1) {
                    dp[i] = dp[i - denominaciones[j]] + 1;
                    monedas[i] = j;
                }
            }
        }
    }

    vector<int> resultado(n, 0);
    if (dp[cambio] == INT_MAX) return resultado;

    int temp = cambio;
    while (temp > 0) {
        int j = monedas[temp];
        resultado[j]++;
        temp -= denominaciones[j];
    }

    return resultado;
}

// Función para encontrar el cambio utilizando un algoritmo avaro
vector<int> cambioAvaro(const vector<int>& denominaciones, int cambio) {
    int n = denominaciones.size();
    vector<int> resultado(n, 0);

    for (int i = n - 1; i >= 0; --i) {
        while (cambio >= denominaciones[i]) {
            cambio -= denominaciones[i];
            resultado[i]++;
        }
    }

    return resultado;
}

int main() {
    int N;
    cin >> N;
    vector<int> denominaciones(N);
    for (int i = 0; i < N; ++i) {
        cin >> denominaciones[i];
    }

    int P, Q;
    cin >> P >> Q;
    int cambio = Q - P;

    // Ordenar las denominaciones de mayor a menor para el algoritmo avaro
    sort(denominaciones.rbegin(), denominaciones.rend());

    vector<int> resultadoDinamico = cambioDinamico(denominaciones, cambio);
    vector<int> resultadoAvaro = cambioAvaro(denominaciones, cambio);

    cout << "Cambio utilizando programación dinámica:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << resultadoDinamico[i] << endl;
    }

    cout << "Cambio utilizando algoritmo avaro:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << resultadoAvaro[i] << endl;
    }

    return 0;
}