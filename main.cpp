#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    string inFileName;

    // settings
    string relativePathPrefix("");

    if (argc == 1) {
        cout << "Input .md file name: ";
        cin >> inFileName;
    } else {
        if (argc == 2) {
            inFileName = string(argv[1]);
        } else {
            cout << "Too many arguments" << endl;
            return 0;
        }
    }
    inFileName = relativePathPrefix + inFileName;
    // cout << inFileName << endl;
    ifstream inFile(inFileName);
    if (!inFile.is_open()) {
        cout << "Error opening the file" << endl;
        return 0;
    }
    return 0;
}
