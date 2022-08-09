// Copyright (C) 2022 Zijun Yang <zijun.yang@outlook.com>
//
// This file is part of Markdown to HTML Convertor.
//
// Markdown to HTML Convertor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Markdown to HTML Convertor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Markdown to HTML Convertor.  If not, see <http://www.gnu.org/licenses/>.

#include "settings.h"
#include <iostream>
#include "stringProcess.h"
using namespace std;
string getTypeName(FileType t) {
    string fileName[10];
    fileName[HTML] = "html";
    fileName[VUE] = "vue";
    return fileName[t];
}
int Settings::set() {
    cout << "Input markdown file path: ";
    cin >> inFileName;
    inFile.open(inFileName);
    if (!inFile.is_open()) {
        cout << "Error opening the markdown file." << endl;
        return 1;
    }
    cout << "Input output file path: ";
    cin >> outFileName;
    outFile.open(outFileName);
    if (!outFile.is_open()) {
        cout << "Error opening output file." << endl;
        return 2;
    }
    if (outFileName.substr(outFileName.length() - 3, 3) == "vue") {
        type = VUE;
    }
    return 0;
}
void Settings::beforeBody() {
    ifstream file("./source/" + getTypeName(type) + "Start.html");
    while (!file.eof()) {
        string theLine;
        getline(file, theLine);
        if (theLine == "thisShouldBeTheTitleOfYourWebsite") {
            theLine = outFileName.substr(0, findChar(outFileName, 0, '.', ""));
        }
        outFile << theLine << endl;
    }
}
void Settings::afterBody() {
    ifstream file("./source/" + getTypeName(type) + "End.html");
    while (!file.eof()) {
        string theLine;
        getline(file, theLine);
        outFile << theLine << endl;
    }
    file.close();
    file.open("./source/defaultCss.html");
    while (!file.eof()) {
        string theLine;
        getline(file, theLine);
        outFile << theLine << endl;
    }
}
