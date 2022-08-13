# A Markdown to HTML Convertor

## Currently supports

`#`, `##`, ... -> `<h1>`, `<h2>`, ...

`---` -> `<hr>`

Unordered/ordered list

`![]()`, `<img>` -> `<img>`

`[]()` -> `<a>`

Plain text

Code blocks (` ``` ``` `)

Inline code blocks (` `` `)

## How to compile

The project uses `CMake` as building tool.

## How to use (in Windows)

1. Download and unzip `markdown2html-x.x.x.zip` from [this page](https://github.com/zijunhz/markdown2html/releases/latest).
2. Open `markdown2html.exe` and follow the instruction:
3. Input Markdown file path: you need to enter the path to your markdown file. This path can be absolute or be relative to the path where the `.exe` locates. ***It is recommended to copy the markdown file into the folder where the exe is located so that you only need to type in the file name of the markdown file.***
4. Input output file path: this is the same as 3, but it specifies where you wish the output file is.
5. Choose theme: enter a number.

## Fun fact

[My website](https://zpatronus.top) is generated by this program.

![effect](docs/Screenshot%202022-08-09%20030738.png)

## Themes

Themes are now supported.

There are a total of 7 themes.

- default
- githubDark
- githubLight
- dark
- light
- darkCompact
- lightCompact
