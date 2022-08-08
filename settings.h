#ifndef A8B8F23B_68D6_41E6_A207_690B54168564
#define A8B8F23B_68D6_41E6_A207_690B54168564
#include <fstream>
#include <iostream>
#include <string>
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
    ifstream inFile;
    ofstream outFile;
    Settings()
        : inFileName(""), outFileName(""), addHtml(false), addCss(false), type(HTML) {}
    string getInFileName() const { return inFileName; }
    string getOutFileName() const { return outFileName; }
    /**
     * @brief get settings from user
     *
     * @return int 0 if everything's fine, other if something went wrong
     */
    int set() {
        cout << "Input markdown file path: ";
        cin >> inFileName;
        inFile.open(inFileName);
        if (!inFile.is_open()) {
            cout << "Error opening the markdown file." << endl;
            return 1;
        }
        cout << "Input output file path: ";
        cin >> outFileName;
        outFile.open(outFileName);
        if (!outFile.is_open()) {
            cout << "Error opening output file." << endl;
            return 2;
        }
        if (outFileName.substr(outFileName.length() - 3, 3) == "vue") {
            type = VUE;
        }
        return 0;
    }
    void beforeBody() {
        if (type == VUE) {
            outFile << "<template>" << endl;
        } else if (type == HTML) {
        }
    }
    void afterBody() {
        if (type == VUE) {
            outFile << "</template>" << endl;
        } else if (type == HTML) {
        }
    }
};

#endif /* A8B8F23B_68D6_41E6_A207_690B54168564 */
