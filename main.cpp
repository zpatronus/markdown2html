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
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "settings.h"
#include "stringProcess.h"
using namespace std;

vector<string> line;
int main() {
    cout << "    markdown2html  Copyright (C) 2022  Zijun Yang <zijun.yang@outlook.com>" << endl
         << "    This program comes with ABSOLUTELY NO WARRANTY." << endl
         << "    This is free software, and you are welcome to redistribute it" << endl
         << "    under certain conditions." << endl;
    Settings s;
    if (s.set() != 0) {
        return 0;
    }
    s.beforeBody();
    convert(s.inFile, s.outFile);
    s.afterBody();
    return 0;
}
