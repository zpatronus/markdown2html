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

#ifndef B04F0136_CA7D_47CC_92DD_F58FDAB6C35E
#define B04F0136_CA7D_47CC_92DD_F58FDAB6C35E

enum Type {
    Text,   // start with
    Uli,    // start with
    Oli,    // start with
    Hr,     // start with
    Title,  // start with
    Img,
    ImgBracket,
    Hyper,
    CodeBlock,  // start with
    InlineCode
};

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "stringProcess.h"
using namespace std;
/**
 * @brief Text, Uli, Oli, Hr, Title, Img, ImgBracket, Hyper
 *
 */

class MarkdownSource {
   protected:
    vector<string> lines;
    // the types here only records start with
    vector<Type> types;
    int size;
    /**
     * @brief use input vector to init
     *
     */
    void copy(vector<string>);

   public:
    MarkdownSource(vector<string>&);
    MarkdownSource(ifstream&);
    int getSize() const { return size; }
    Type type(int i) const {
        if (i < 0 || i >= size) {
            cout << "get type() error: index out of boundary";
            return Text;
        }
        return types[i];
    }
    string l(int i) const {
        if (i < 0 || i >= size) {
            cout << "get l() error: index out of boundary";
            return "";
        }
        return lines[i];
    }
    void convertTo(ofstream&);
};

#endif /* B04F0136_CA7D_47CC_92DD_F58FDAB6C35E */
