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

#ifndef DE99A324_78F6_4041_9C09_5DB4135F2509
#define DE99A324_78F6_4041_9C09_5DB4135F2509
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/**
 * @brief Text, Uli, Oli, Hr, Title, Img, ImgBracket, Hyper
 *
 */
enum Type {
    Text,   // start with
    Uli,    // start with
    Oli,    // start with
    Hr,     // start with
    Title,  // start with
    Img,
    ImgBracket,
    Hyper
};
/**
 * @brief judge string s[startFrom]~s[s.len] start from what
 *
 * @param s the string
 * @param startFrom index that start judging from
 * @return Type
 */
Type startWith(string& s, int startFrom);
/**
 * @brief Get the Url
 *
 * @param s the string
 * @param startFrom index that start judging from
 * @return string
 */
string getUrl(string& s, int startFrom);
/**
 * @brief Get the Alt
 *
 * @param s the string
 * @param startFrom index that start from judging from
 * @return string
 */
string getAlt(string& s, int startFrom);
/**
 * @brief find the position of c in s starting from startFrom
 *
 * @param s the string
 * @param startFrom index that from which starts judging
 * @param c
 * @param exclude if there's any char in between c and start, return -1
 * @return int -1 if failed, otherwise the index
 */
int findChar(string& s, int startFrom, char c, string exclude);
/**
 * @brief judge whether s consists of only space and \n
 *
 * @param s
 * @return true
 * @return false
 */
bool isEmpty(string& s);
/**
 * @brief find the index of the first digit in s starting from startFrom
 *
 * @param s
 * @param startFrom
 * @return int
 */
int findDigit(string& s, int startFrom);
/**
 * @brief preprocess lines; removing blank lines
 *
 * @param oldLine
 * @return vector<string>
 */
vector<string> preProcess(ifstream& inFile);
/**
 * @brief convert line(markdown) to outFile(html)
 *
 * @param outFile
 * @param line
 */
void convert(ifstream& inFile, ofstream& outFile);
#endif /* DE99A324_78F6_4041_9C09_5DB4135F2509 */
