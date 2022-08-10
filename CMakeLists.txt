cmake_minimum_required(VERSION 3.0.0)
project(markdown2html VERSION 1.0.0)

add_compile_options(-Wall -Wextra -Wpedantic -std=c++1z)

add_executable(markdown2html main.cpp stringProcess.cpp stringProcess.h Settings.h Settings.cpp MarkdownSource.h)
