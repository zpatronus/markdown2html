# A Markdown to HTML Convertor

## Currently supports

`#`, `##`, ... -> `<h1>`, `<h2>`, ...

`---` -> `<hr>`

Unordered/ordered list

`![]()`, `<img>` -> `<img>`

`[]()` -> `<a>`

Plain text

## Some markdown format requirements

- There should be no blank lines in an unordered/ordered list.
- Ordered list and unordered list cannot be in the same level while next to each other.

## How to compile

The project uses `CMake` as building tool.
