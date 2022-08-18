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

#include "Settings.h"
#include <iomanip>
#include <iostream>
#include <string>
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
    if (inFile != nullptr) {
        delete inFile;
    }
    inFile = new ifstream;
    inFile->open(inFileName);
    if (!inFile->is_open()) {
        cout << "Error opening the markdown file." << endl;
        return 1;
    }
    cout << "Input output file path: ";
    cin >> outFileName;
    if (outFile != nullptr) {
        delete outFile;
    }
    outFile = new ofstream;
    outFile->open(outFileName);
    if (!outFile->is_open()) {
        cout << "Error opening output file." << endl;
        return 2;
    }
    if (outFileName.substr(outFileName.length() - 3, 3) == "vue") {
        type = VUE;
    }
    return 0;
}
int Settings::set(string inFileName, string outFileName, bool addHtml = true, bool addCss = true) {
    this->inFileName = inFileName;
    this->outFileName = outFileName;
    this->addHtml = addHtml;
    this->addCss = addCss;
    if (inFile != nullptr) {
        delete inFile;
    }
    inFile = new ifstream;
    inFile->open(inFileName);
    if (!inFile->is_open()) {
        cout << "Error opening the markdown file." << endl;
        return 1;
    }
    if (outFile != nullptr) {
        delete outFile;
    }
    outFile = new ofstream;
    outFile->open(outFileName);
    if (!outFile->is_open()) {
        cout << "Error opening output file." << endl;
        return 2;
    }
    if (outFileName.substr(outFileName.length() - 3, 3) == "vue") {
        type = VUE;
    }
    return 0;
}
void Settings::beforeBody() {
    ifstream file("./source/html/" + getTypeName(type) + "Start.html");
    while (!file.eof()) {
        string theLine;
        getline(file, theLine);
        if (theLine == "thisShouldBeTheTitleOfYourWebsite") {
            theLine = outFileName.substr(0, findChar(outFileName, 0, '.', ""));
        }
        *outFile << theLine << endl;
    }
}
string selectTheme() {
    vector<string> themes;
    themes.push_back("default");
    themes.push_back("githubLight");
    themes.push_back("githubDark");
    themes.push_back("light");
    themes.push_back("dark");
    themes.push_back("lightCompact");
    themes.push_back("darkCompact");
    cout << "Pick your theme:" << endl;
    for (int i = 0; i < (int)themes.size(); i++) {
        cout << setw(2) << right << i << ": " << setw(14) << left << themes[i] << endl;
    }
    cout << "Enter number to choose theme; default: 0" << endl
         << "> ";
    string s;
    fflush(stdin);
    getline(cin, s);
    int res = stoi("0" + s);
    if (!(0 <= res && res < (int)themes.size())) {
        res = 0;
    }
    return themes[res];
}
void Settings::afterBody() {
    ifstream file("./source/html/" + getTypeName(type) + "End.html");
    while (!file.eof()) {
        string theLine;
        getline(file, theLine);
        *outFile << theLine << endl;
    }
    file.close();
    // select style
    file.open("./source/css/" + selectTheme() + ".css");
    if (!(file.is_open())) {
        cout << "Error opening css file" << endl;
        return;
    }
    *outFile << "<style>" << endl;
    while (!file.eof()) {
        string theLine;
        getline(file, theLine);
        *outFile << theLine << endl;
    }
    *outFile << "</style>" << endl;
}
int MultiSettings::set() {
    string s1, s2;
    cout << "Input markdown file path(s): ";
    cin >> s1;
    s1 = s1 + " ";
    cout << "Input output file path(s); leave blank to set automatically: ";
    cin >> s2;
    s2 = s2 + " ";
    int i1 = 0, i2 = 0;
    int l1 = s1.length();
    int l2 = s2.length();
    while (i1 < l1 && s1[i1] == ' ') {
        i1++;
    }
    while (i2 < l2 && s2[i2] == ' ') {
        i2++;
    }
    if (isEmpty(s2)) {
        while (!isEmpty(s1, i1)) {
            Settings theSettings;
            string fileName = fileNameStartFrom(s1, i1);
            if (theSettings.set(fileName, pureFileName(fileName) + ".html", true, true) != 0) {
                return settingsVec.size() + 1;
            }

            // settingsVec.insert(settingsVec.end(), theSettings);
        }
    } else {
    }
    return 0;
}
