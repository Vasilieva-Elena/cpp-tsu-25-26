#include "SingleLineFile.h"
#include <iostream>

SingleLineFile::SingleLineFile(const std::string& n, const std::string& c)
    : Entry(n), content(c) {}

std::string SingleLineFile::displayName() const {
    return name;
}

void SingleLineFile::edit() {
    std::cout << "Editing single-line file. Enter new content:\n";
    std::string newContent;
    std::getline(std::cin, newContent);
    content = newContent;
    std::cout << "File updated.\n";
}

void SingleLineFile::hide() {
    if (!hidden) {
        hidden = true;
        if (name[0] != '.') name = "." + name;
    }
}

void SingleLineFile::restore() {
    if (hidden) {
        hidden = false;
        if (name[0] == '.') name = name.substr(1);
    }
}

std::string SingleLineFile::getContent() const {
    return content;
}

void SingleLineFile::setContent(const std::string& c) {
    content = c;
}
