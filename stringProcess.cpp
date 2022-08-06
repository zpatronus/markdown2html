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
#include <string>
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
