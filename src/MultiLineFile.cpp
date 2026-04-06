#include "MultiLineFile.h"
#include <iostream>
#include <sstream>

MultiLineFile::MultiLineFile(const std::string& n, const std::vector<std::string>& l)
    : Entry(n), lines(l) {}

std::string MultiLineFile::displayName() const {
    return name;
}

void MultiLineFile::edit() {
    std::cout << "Editing multi-line file. Options:\n";
    std::cout << "1) Edit existing line by number\n";
    std::cout << "2) Append lines (enter '-1' to finish)\n";
    std::cout << "Choose (1/2): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        std::cout << "Enter line number (1.." << lines.size() << "): ";
        size_t lineNum;
        std::cin >> lineNum;
        std::cin.ignore();
        if (lineNum >= 1 && lineNum <= lines.size()) {
            std::cout << "New content for line " << lineNum << ": ";
            std::string newLine;
            std::getline(std::cin, newLine);
            lines[lineNum - 1] = newLine;
            std::cout << "Line updated.\n";
        } else {
            std::cout << "Invalid line number.\n";
        }
    } else if (choice == 2) {
        std::cout << "Enter lines (enter '-1' on a new line to stop):\n";
        std::string line;
        while (true) {
            std::getline(std::cin, line);
            if (line == "-1") break;
            lines.push_back(line);
        }
        std::cout << "Lines appended.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void MultiLineFile::hide() {
    if (!hidden) {
        hidden = true;
        if (name[0] != '.') name = "." + name;
    }
}

void MultiLineFile::restore() {
    if (hidden) {
        hidden = false;
        if (name[0] == '.') name = name.substr(1);
    }
}

std::string MultiLineFile::getContent() const {
    std::ostringstream oss;
    for (size_t i = 0; i < lines.size(); ++i) {
        oss << (i+1) << ": " << lines[i] << "\n";
    }
    return oss.str();
}

void MultiLineFile::setContent(const std::vector<std::string>& l) {
    lines = l;
}
