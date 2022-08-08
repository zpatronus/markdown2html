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
    string s[10];
    s[VUE] = "<div>\n<template>\n";
    s[HTML] = "<!DOCTYPE html><html lang = \"en\" ><head><meta charset = \"UTF-8\"><meta http-equiv = \"X-UA-Compatible\" content = \"IE=edge\"><meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\"><title>" + outFileName.substr(0, findChar(outFileName, 0, '.', "")) + "</title></head><body>\n\n";
    outFile << s[type];
}
void Settings::afterBody() {
    string s[10];
    s[VUE] = "</div>\n</template>\n";
    s[HTML] = "\n\n</body></html>\n";
    outFile << s[type];
}
