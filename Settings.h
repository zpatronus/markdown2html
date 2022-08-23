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

#ifndef A8B8F23B_68D6_41E6_A207_690B54168564
#define A8B8F23B_68D6_41E6_A207_690B54168564
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum FileType {
    HTML,
    VUE
};

class Settings {
   protected:
    string inFileName, outFileName;
    bool addHtml;
    bool addCss;
    FileType type;

   public:
    ifstream* inFile;
    ofstream* outFile;
    Settings()
        : inFileName(""), outFileName(""), addHtml(true), addCss(true), type(HTML), inFile(nullptr), outFile(nullptr) {}
    ~Settings() {
        if (inFile != nullptr) {
            inFile->close();
            delete inFile;
        }
        if (outFile != nullptr) {
            outFile->close();
            delete outFile;
        }
    }
    string getInFileName() const { return inFileName; }
    string getOutFileName() const { return outFileName; }
    /**
     * @brief get settings from user
     *
     * @return int 0 if everything's fine, other if something went wrong
     */
    int set();
    /**
     * @brief get settings from arg
     *
     * @param inFileName
     * @param outFileName
     * @param addHtml
     * @param addCss
     * @return int
     */
    int set(string inFileName, string outFileName, bool addHtml, bool addCss);
    /**
     * @brief lines added before the body, such as <head>, <template>
     *
     */
    void beforeBody();
    /**
     * @brief lines added after the body, such as <style>
     *
     */
    void afterBody(string theme = "noThemeSelected");
    void convert(string theme = "noThemeSelected");
};

class MultiSettings {
   protected:
    vector<Settings*> settingsVec;
    string theme;

   public:
    int set();
    void convert();
};

void createDir(string outFileName);

#endif /* A8B8F23B_68D6_41E6_A207_690B54168564 */
