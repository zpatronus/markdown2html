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

#include "stringProcess.h"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int findDigit(string& s, int startFrom) {
    int len = s.length();
    for (int i = startFrom; i < len; i++) {
        if (isdigit(s[i])) {
            return i;
        }
    }
    return -1;
}
bool isEmpty(string& s) {
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] != ' ' && s[i] != '\n' && s[i] != '\0') {
            return false;
        }
    }
    return true;
}
string getUrl(string& s, int startFrom) {
    int startPos = findChar(s, startFrom, '(', ""), endPos = findChar(s, startFrom, ')', "");
    return s.substr(startPos + 1, endPos - startPos - 1);
}
string getAlt(string& s, int startFrom) {
    int startPos = findChar(s, startFrom, '[', ""), endPos = findChar(s, startFrom, ']', "");
    return s.substr(startPos + 1, endPos - startPos - 1);
}
int findChar(string& s, int startFrom, char c, string exclude) {
    int len = s.length(), lenEx = exclude.length();
    for (int i = startFrom; i < len; i++) {
        if (s[i] == c) {
            return i;
        }
        for (int j = 0; j < lenEx; j++) {
            if (s[i] == exclude[j]) {
                return -1;
            }
        }
    }
    return -1;
}
Type startWith(string& s, int startFrom) {
    if (s.substr(startFrom, 4) == "<img") {
        return Img;
    }
    int len = s.length();
    if (startFrom == 0) {
        if (s.substr(0, 3) == "---") {
            return Hr;
        }
        // Title
        bool isTitle = s[0] == '#';
        for (int i = 1; i < len; i++) {
            if (s[i] == ' ') {
                break;
            }
            if (s[i] != '#') {
                isTitle = false;
                break;
            }
        }
        if (isTitle) {
            return Title;
        }
        // Uli
        bool isUli = true;
        for (int i = 0; i < len; i++) {
            if (s[i] == ' ') {
                continue;
            }
            if (s.substr(i, 2) == "- ") {
                break;
            }
            isUli = false;
            break;
        }
        if (isUli) {
            return Uli;
        }
        // Oli
        int dotPos = findChar(s, 0, '.', "");
        if (dotPos != -1 && s.substr(dotPos, 2) == ". ") {
            bool isOli = true, inDigit = false;
            for (int i = 0; i < dotPos; i++) {
                if ((!inDigit) && s[i] == ' ') {
                    continue;
                }
                if (isdigit(s[i])) {
                    inDigit = true;
                    continue;
                }
                isOli = false;
                break;
            }
            if (isOli) {
                return Oli;
            }
        }
    }
    // ImgBracket
    if (s.substr(startFrom, 2) == "![") {
        int pos = findChar(s, startFrom + 2, ']', "");
        if (pos != -1 && s.substr(pos + 1, 1) == "(") {
            pos = findChar(s, pos + 2, ')', "");
        }
        if (pos != -1) {
            return ImgBracket;
        }
    }
    // Hyper
    if (s.substr(startFrom, 1) == "[") {
        int pos = findChar(s, startFrom + 2, ']', "");
        if (pos != -1 && s.substr(pos + 1, 1) == "(") {
            pos = findChar(s, pos + 2, ')', "");
        }
        if (pos != -1) {
            return Hyper;
        }
    }
    return Text;
}
vector<string> preProcess(ifstream& inFile) {
    vector<string> v;
    while (!inFile.eof()) {
        string theLine;
        getline(inFile, theLine);
        if (v.empty() || (!(isEmpty(theLine) && isEmpty(v.back())))) {
            v.push_back(theLine);
        }
    }
    v.push_back("\n");
    // for (auto i : res) {
    //     cout << i << endl;
    // }
    // when should a blank res be removed?
    // 1. res[n] is blank
    // 2. any blank res between two list items
    vector<string> res;
    for (auto vi = v.begin(); vi != v.end(); vi++) {
        bool canPush = true;
        if (isEmpty(*vi)) {
            if (!res.empty()) {
                if (isEmpty(res.back())) {
                    canPush = false;
                }
            } else {
                canPush = false;
            }
        } else if (res.size() >= 2) {
            Type last2 = startWith(res[res.size() - 2], 0), now = startWith(*vi, 0);
            if ((now == Uli || now == Oli) && (isEmpty(res.back())) && (last2 == Uli || last2 == Oli)) {
                res.pop_back();
            }
        }
        if (canPush) {
            res.push_back(*vi);
        }
    }
    return res;
}
void convert(ifstream& inFile, ofstream& outFile) {
    vector<string> line = preProcess(inFile);
    Type lType[100] = {Text};
    int lNum[100] = {0}, lSize = 0, index = -1;
    lNum[0] = -10;
    for (auto l : line) {
        index++;
        int i = 0, len = l.length();
        if (len == 0) {
            if (lSize == 0) {
                if (index > 0 && index < (int)line.size() - 1 && line[index - 1].length() > 0 && line[index + 1].length() > 0 && startWith(line[index - 1], 0) == Text && startWith(line[index + 1], 0) == Text) {
                    outFile << "<br>" << endl;
                }
            } else {
                while (lSize > 0) {
                    outFile << "</li>" << endl
                            << ((lType[lSize] == Uli)
                                    ? "</ul>"
                                    : "</ol>")
                            << endl;
                    lSize--;
                }
            }
            continue;
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
            if (theType == Uli || theType == Oli) {
                string meStart = "<ul>", meEnd = "</ul>", youStart = "<ol>", youEnd = "</ol>";
                if (theType == Oli) {
                    swap(meEnd, youEnd);
                    swap(meStart, youStart);
                }
                int indentCnt = (theType == Uli) ? findChar(l, i, '-', "") : findDigit(l, i);
                if (lType[lSize] == theType && lNum[lSize] == indentCnt) {
                    outFile << "</li>" << endl;
                } else if (indentCnt - lNum[lSize] >= 2) {
                    lSize++;
                    lNum[lSize] = indentCnt;
                    lType[lSize] = theType;
                    outFile << meStart << endl;
                } else {
                    // not the same type of list or higher level
                    while (lSize > 0 && ((lType[lSize] != theType && lNum[lSize] == indentCnt) || lNum[lSize] - indentCnt >= 2)) {
                        outFile
                            << "</li>" << endl
                            << (lType[lSize] == theType ? meEnd : youEnd) << endl;
                        lSize--;
                    }
                    if (lSize > 0 && lType[lSize] == theType) {
                        // same level & same type
                        outFile << "</li>" << endl;
                    } else {
                        // different level || different type
                        lSize++;
                        lNum[lSize] = indentCnt;
                        lType[lSize] = theType;
                        outFile << meStart << endl;
                    }
                }
                outFile << "<li>" << endl;
                i = (theType == Uli) ? indentCnt + 2 : findChar(l, indentCnt, '.', "") + 2;
            }
            if (theType == Text) {
                outFile << l[i];
                i++;
            }
        }
        outFile << endl;
    }
}
