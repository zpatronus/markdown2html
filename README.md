# A Markdown to HTML Convertor

## For users

### The convertor currently supports

- `#`, `##`, ... -> `<h1>`, `<h2>`, ...
- `---` -> `<hr>`
- Unordered/ordered list
- `![]()`, `<img>` -> `<img>`
- `[]()` -> `<a>`
- Plain text
- Code blocks (` ``` ``` `)
- Inline code blocks (` `` `)

### How to use (in Windows)

1. Download and unzip `markdown2html-x.x.x.zip` from [this page](https://github.com/zijunhz/markdown2html/releases/latest).
2. Open `markdown2html.exe` and follow the instruction:
3. Input Markdown file path: you need to enter the path to your markdown file. This path can be absolute or be relative to the path where the `.exe` locates. ***It is recommended to copy the markdown file into the folder where the exe is located so that you only need to type in the file name of the markdown file.***
4. Input output file path: this is the same as 3, but it specifies where you wish the output file is.
5. Choose theme: enter a number.

### Fun fact

[My website](https://zpatronus.top) is generated by this program.

![effect](https://media.githubusercontent.com/media/zpatronus/markdown2html/main/docs/Screenshot%202022-08-09%20030738.png)

### Themes

Themes are now supported.

There are a total of 7 themes.

- default
- githubDark
- githubLight
- dark
- light
- darkCompact
- lightCompact

## For developers

[Github Repo](https://github.com/zijunhz/markdown2html)

### How to compile

The project uses `CMake` as building tool.

### Structure of the project

[![z1s2TK.png](https://s1.ax1x.com/2022/11/22/z1s2TK.png)](https://imgse.com/i/z1s2TK)

### Core function `convertTo(ofstream&)`

Effect: convert a Markdown source to a HTML/Vue source into a given ofstream passed by reference.

`lNum`, `lType` are two stack used to deal with nested ordered/unordered list.

```cpp
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
```
