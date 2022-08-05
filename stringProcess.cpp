#include "stringProcess.h"
#include <string>
using namespace std;
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
