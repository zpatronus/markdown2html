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
#include "MarkdownSource.h"
#include <fstream>
#include "stringProcess.h"
// #include <iostream>
#include <vector>
using namespace std;
void MarkdownSource::copy(vector<string> v) {
    size = v.size();
    lines = v;
    bool isInCodeBlock = false;
    for (auto l : lines) {
        Type theType = startWith(l, 0);
        if (isInCodeBlock) {
            types.push_back(CodeBlock);
            if (theType == CodeBlock) {
                isInCodeBlock = false;
            }
        } else {
            types.push_back(theType);
            if (theType == CodeBlock) {
                isInCodeBlock = true;
            }
        }
    }
}
MarkdownSource::MarkdownSource(vector<string>& v) {
    copy(v);
}
MarkdownSource::MarkdownSource(ifstream& inFile) {
    copy(preProcess(inFile));
}
void MarkdownSource::convertTo(ofstream& outFile) {
    Type lType[100] = {Text};
    int lNum[100] = {0}, lSize = 0, index = -1;
    lNum[0] = -10;
    bool isInCodeBlocks = false;
    for (auto l : lines) {
        index++;
        int i = 0, len = l.length();
        if (types[index] == CodeBlock) {
            if (l.substr(0, 3) == "```") {
                if (!isInCodeBlocks) {
                    outFile << "<pre>" << endl;
                } else {
                    outFile << "</pre>" << endl;
                }
                isInCodeBlocks = !isInCodeBlocks;
            } else {
                outFile << l << endl;
            }
            continue;
        }
        if (len == 0) {
            if (lSize == 0) {
                if (index > 0 && index < size - 1 && lines[index - 1].length() > 0 && lines[index + 1].length() > 0 && startWith(lines[index - 1], 0) == Text && startWith(lines[index + 1], 0) == Text) {
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

        Type theType = startWith(l, 0);

        if (theType == Hr) {
            outFile << "<hr>";
            continue;
        }

        if (theType == Title) {
            int spacePos = findChar(l, i, ' ', "");
            outFile << "<h" << spacePos << ">" << endl;
            processLine(l, spacePos + 1, outFile);
            outFile << "</h" << spacePos << ">" << endl;
            continue;
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
            processLine(l, (theType == Uli) ? indentCnt + 2 : findChar(l, indentCnt, '.', "") + 2, outFile);
            continue;
        }
        processLine(l, 0, outFile);
    }
}
