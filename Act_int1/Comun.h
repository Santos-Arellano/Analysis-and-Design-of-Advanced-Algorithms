#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<string> encontrarStrings(const string& filename) {
    ifstream file(filename);
    vector<string> lines;

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}