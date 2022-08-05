#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "stringProcess.h"
using namespace std;

vector<string> line;
int main(int argc, char* argv[]) {
    // ==================== input file name and opening file
    string inFileName;
    if (argc == 1) {
        cout << "Input .md file path: ";
        cin >> inFileName;
    } else {
        if (argc == 2) {
            inFileName = string(argv[1]);
        } else {
            cout << "Too many arguments" << endl;
            return 0;
        }
    }
    // cout << inFileName << endl;
    ifstream inFile(inFileName);
    if (!inFile.is_open()) {
        cout << "Error opening the file" << endl;
        return 0;
    }
    // ==================== store file into vector line
    while (!inFile.eof()) {
        string theLine;
        getline(inFile, theLine);
        line.push_back(theLine);
    }
    line.push_back("\n");
    // for (auto i : line) {
    //     cout << i << endl;
    // }
    // ===================== output file
    string outFileName;
    cout << "Input .html file path: ";
    cin >> outFileName;
    ofstream outFile(outFileName);
    // processing
    Type listType[100] = {Text};
    int listNum[100] = {0}, listSize = 0;
    listNum[0] = -10;
    for (auto l : line) {
        int i = 0, len = l.length();
        if (len == 0) {
            while (listSize > 0) {
                outFile << "</li>" << endl;
                if (listType[listSize] != Uli) {
                    outFile << "</ol>" << endl;
                } else {
                    outFile << "</ul>" << endl;
                }
                listSize--;
            }
        }
        while (i < len) {
            Type theType = startWith(l, i);
            if (theType == Hr) {
                outFile << "<hr>";
                break;
            }
            if (theType == ImgBracket) {
                outFile << "<img src=\"" + getUrl(l, i) + "\"alt=\"" + getAlt(l, i) + "\">";
                i = findChar(l, i, ')', "") + 1;
            }
            if (theType == Hyper) {
                outFile << "<a href=\"" + getUrl(l, i) + "\">" + getAlt(l, i) + "</a>";
                i = findChar(l, i, ')', "") + 1;
            }
            if (theType == Img) {
                int endPos = findChar(l, i, '>', "");
                outFile << l.substr(i, endPos - i + 1);
                i = endPos + 1;
            }
            if (theType == Title) {
                int spacePos = findChar(l, i, ' ', "");
                outFile << "<h" << spacePos << ">" + l.substr(spacePos + 1, l.length() - spacePos - 1) + "</h" << spacePos << ">";
                break;
            }
            if (theType == Uli) {
                int dashPos = findChar(l, i, '-', "");
                if (listType[listSize] == Uli && listNum[listSize] == dashPos) {
                    outFile << "</li>" << endl;
                }
                if (dashPos - listNum[listSize] >= 2) {
                    listSize++;
                    listNum[listSize] = dashPos;
                    listType[listSize] = Uli;
                    outFile << "<ul>" << endl;
                } else {
                    bool isPop = false;
                    while (listSize > 0 && (listType[listSize] != Uli || listNum[listSize] - dashPos >= 2)) {
                        outFile << "</li>" << endl;
                        if (listType[listSize] != Uli) {
                            outFile << "</ol>" << endl;
                        } else {
                            outFile << "</ul>" << endl;
                        }
                        listSize--;
                        isPop = true;
                    }
                    if (isPop) {
                        outFile << "</li>" << endl;
                    }
                }
                outFile << "<li>";
                i = dashPos + 2;
            }
            if (theType == Text) {
                outFile << l[i];
                i++;
            }
        }
        outFile << endl;
    }
    return 0;
}
