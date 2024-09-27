#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Comun.h"
#include "Palindromo.h"

using namespace std;

string readFile(const string& filename) {
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return content;
}

bool isContained(const string& transmission, const string& mcode, int& position) {
    size_t found = transmission.find(mcode);
    if (found != string::npos) {
        position = found + 1;
        return true;
    }
    return false;
}

pair<int, int> findLongestCommonSubstring(const string &s1, const string &s2) {
    int maxLength = 0;
    int endPos = 0;
    vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1, 0));

    for (int i = 1; i <= s1.length(); i++) {
        for (int j = 1; j <= s2.length(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endPos = i;
                }
            }
        }
    }

    return {endPos - maxLength + 1, endPos};
}

int main() {
    vector<string> transmissions = {"transmission1.txt", "transmission2.txt"};
    vector<string> mcodes = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};
    
    // Parte 1
    for (const auto& transmission : transmissions) {
        string trans_content = readFile(transmission);
        for (const auto& mcode : mcodes) {
            string mcode_content = readFile(mcode);
            int position;
            bool contained = isContained(trans_content, mcode_content, position);
            cout << (contained ? "true " + to_string(position) : "false") << endl;
        }
    }

    // Parte 2
    for (const auto& transmission : transmissions) {
        string trans_content = readFile(transmission);
        pair<int, int> result = findLongestPalindrome(trans_content);
        cout << result.first << " | " << result.second << endl;
    }

    // Parte 3
    string trans1_content = readFile("transmission1.txt");
    string trans2_content = readFile("transmission2.txt");
    pair<int, int> commonResult = findLongestCommonSubstring(trans1_content, trans2_content);
    cout << commonResult.first << " " << commonResult.second << endl;

    return 0;
}


//g++ -std=c++11 E_1.cpp -o E_1