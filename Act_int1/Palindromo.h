#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Result {
    string match;
    int beginIndex;
    int endIndex;
};

// Función para encontrar el palíndromo más largo en un vector de caracteres
pair<int, int> findLongestPalindrome(const string &combined) {
    if (combined.empty()) return {0, 0};

    int n = combined.length();
    int longestBegin = 0, longestEnd = 0;
    int longestLength = 0;

    for (int i = 0; i < n; i++) {
        // Chequear palíndromos de longitud impar
        int left = i, right = i;
        while (left >= 0 && right < n && combined[left] == combined[right]) {
            int length = right - left + 1;
            if (length > longestLength) {
                longestLength = length;
                longestBegin = left;
                longestEnd = right;
            }
            left--;
            right++;
        }

        // Chequear palíndromos de longitud par
        left = i;
        right = i + 1;
        while (left >= 0 && right < n && combined[left] == combined[right]) {
            int length = right - left + 1;
            if (length > longestLength) {
                longestLength = length;
                longestBegin = left;
                longestEnd = right;
            }
            left--;
            right++;
        }
    }

    // Retornar las posiciones (iniciando en 1)
    return {longestBegin + 1, longestEnd + 1}; 
}


