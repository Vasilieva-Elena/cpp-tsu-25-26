#include "PostponedFile.h"
#include <iostream>
#include <stdexcept>

PostponedFile::PostponedFile(const std::string& n) : Entry(n) {}

std::string PostponedFile::displayName() const {
    return name;
}

void PostponedFile::edit() {
    // В реальном коде этот метод не должен вызываться напрямую.
    // Замена происходит в Terminal::edit().
    throw std::runtime_error("PostponedFile must be replaced before editing.");
}

void PostponedFile::hide() {
    if (!hidden) {
        hidden = true;
        if (name[0] != '.') name = "." + name;
    }
}

void PostponedFile::restore() {
    if (hidden) {
        hidden = false;
        if (name[0] == '.') name = name.substr(1);
    }
}

std::string PostponedFile::getContent() const {
    return "";
}

void PostponedFile::setContent(const std::string&) {}
