#include "Comun.h"
#include "Palindromo.h"

using namespace std;

string readFile(const string& filename) {
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
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
        pair<int, int> result = findLongestPalindrome(transmission);
        cout << result.first << " | " << result.second << endl;
    }

    //Parte 3
    vector<string> trans1_lineas = encontrarStrings("transmission1.txt");
    vector<string> trans2_lineas = encontrarStrings("transmission2.txt");
    for (const auto& trans1_linea : trans1_lineas){
        for (const auto& trans2_linea : trans2_lineas){
            if (trans1_linea == trans2_linea){
                cout<<"string en comun"<< endl;
            } 
        }
    }

    return 0;
}