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

#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "settings.h"
#include "stringProcess.h"
using namespace std;

vector<string> line;
int main() {
    Settings s;
    if (s.set() != 0) {
        return 0;
    }
    // ==================== store file into vector line
    while (!s.inFile.eof()) {
        string theLine;
        getline(s.inFile, theLine);
        if (line.empty() || (!(isEmpty(theLine) && isEmpty(line.back())))) {
            line.push_back(theLine);
        }
    }
    line.push_back("\n");
    line = preProcess(line);
    // for (auto i : line) {
    //     cout << i << endl;
    // }
    // ===================== output file
    s.beforeBody();
    // processing
    Type lType[100] = {Text};
    int lNum[100] = {0}, lSize = 0, index = -1;
    lNum[0] = -10;
    for (auto l : line) {
        index++;
        int i = 0, len = l.length();
        if (len == 0) {
            if (lSize == 0) {
                if (index > 0 && index < (int)line.size() - 1 && line[index - 1].length() > 0 && line[index + 1].length() > 0 && startWith(line[index - 1], 0) == Text && startWith(line[index + 1], 0) == Text) {
                    s.outFile << "<br>" << endl;
                }
            } else {
                while (lSize > 0) {
                    s.outFile << "</li>" << endl
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
                s.outFile << "<hr>";
                break;
            }
            if (theType == ImgBracket) {
                s.outFile << "<img src=\"" + getUrl(l, i) + "\"alt=\"" + getAlt(l, i) + "\">";
                i = findChar(l, i, ')', "") + 1;
            }
            if (theType == Hyper) {
                s.outFile << "<a href=\"" + getUrl(l, i) + "\">" + getAlt(l, i) + "</a>";
                i = findChar(l, i, ')', "") + 1;
            }
            if (theType == Img) {
                int endPos = findChar(l, i, '>', "");
                s.outFile << l.substr(i, endPos - i + 1);
                i = endPos + 1;
            }
            if (theType == Title) {
                int spacePos = findChar(l, i, ' ', "");
                s.outFile << "<h" << spacePos << ">" + l.substr(spacePos + 1, l.length() - spacePos - 1) + "</h" << spacePos << ">";
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
                    s.outFile << "</li>" << endl;
                } else if (indentCnt - lNum[lSize] >= 2) {
                    lSize++;
                    lNum[lSize] = indentCnt;
                    lType[lSize] = theType;
                    s.outFile << meStart << endl;
                } else {
                    // not the same type of list or higher level
                    while (lSize > 0 && ((lType[lSize] != theType && lNum[lSize] == indentCnt) || lNum[lSize] - indentCnt >= 2)) {
                        s.outFile
                            << "</li>" << endl
                            << (lType[lSize] == theType ? meEnd : youEnd) << endl;
                        lSize--;
                    }
                    if (lSize > 0 && lType[lSize] == theType) {
                        // same level & same type
                        s.outFile << "</li>" << endl;
                    } else {
                        // different level || different type
                        lSize++;
                        lNum[lSize] = indentCnt;
                        lType[lSize] = theType;
                        s.outFile << meStart << endl;
                    }
                }
                s.outFile << "<li>" << endl;
                i = (theType == Uli) ? indentCnt + 2 : findChar(l, indentCnt, '.', "") + 2;
            }
            if (theType == Text) {
                s.outFile << l[i];
                i++;
            }
        }
        s.outFile << endl;
    }
    s.afterBody();
    return 0;
}
