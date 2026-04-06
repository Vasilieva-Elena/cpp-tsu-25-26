#include "Terminal.h"
#include "Directory.h"
#include "SingleLineFile.h"
#include "MultiLineFile.h"
#include "PostponedFile.h"
#include <iostream>
#include <sstream>
#include <memory>

Terminal::Terminal() {
    root = std::make_shared<Directory>("");
    path.push_back(root);
}

std::shared_ptr<Directory> Terminal::currentDir() {
    return path.back();
}

void Terminal::list() {
    auto dir = currentDir();
    for (auto& entry : dir->listAll()) {
        if (!entry->isHidden()) {
            std::cout << entry->displayName() << "\n";
        }
    }
}

void Terminal::listAllHidden() {
    auto dir = currentDir();
    for (auto& entry : dir->listAll()) {
        std::cout << entry->displayName();
        if (entry->isHidden()) std::cout << " (hidden)";
        std::cout << "\n";
    }
}

void Terminal::cd(const std::string& dirName) {
    if (dirName == "..") {
        if (path.size() > 1) {
            path.pop_back();
        } else {
            std::cout << "Already at root.\n";
        }
        return;
    }

    auto dir = currentDir();
    auto child = dir->findChild(dirName);
    if (!child) {
        std::cout << "No such entry: " << dirName << "\n";
        return;
    }
    auto subdir = child->asDirectory();
    if (!subdir) {
        std::cout << dirName << " is not a directory.\n";
        return;
    }
    path.push_back(subdir);
}

void Terminal::cat(const std::string& fileName) {
    auto dir = currentDir();
    auto entry = dir->findChild(fileName);
    if (!entry) {
        std::cout << "File not found.\n";
        return;
    }
    if (entry->asDirectory()) {
        std::cout << "Cannot cat a directory.\n";
        return;
    }
    std::cout << entry->getContent() << "\n";
}

void Terminal::touch(const std::string& fileName) {
    auto dir = currentDir();
    if (dir->findChild(fileName)) {
        std::cout << "Entry already exists.\n";
        return;
    }
    auto pf = std::make_shared<PostponedFile>(fileName);
    dir->addChild(pf);
    std::cout << "File created (type undefined). Use 'edit' to set type and content.\n";
}

void Terminal::mkdir(const std::string& dirName) {
    auto dir = currentDir();
    if (dir->findChild(dirName)) {
        std::cout << "Entry already exists.\n";
        return;
    }
    auto newDir = std::make_shared<Directory>(dirName);
    dir->addChild(newDir);
    std::cout << "Directory created.\n";
}

void Terminal::rm(const std::string& name) {
    auto dir = currentDir();
    auto entry = dir->findChild(name);
    if (!entry) {
        std::cout << "Entry not found.\n";
        return;
    }
    entry->hide();
    std::cout << "Entry hidden (soft delete). Use 'restore' to recover.\n";
}

void Terminal::restore(const std::string& name) {
    auto dir = currentDir();
    auto entry = dir->findChild("." + name);
    if (!entry) {
        std::cout << "No hidden entry with name " << name << " found.\n";
        return;
    }
    entry->restore();
    std::cout << "Entry restored.\n";
}

void Terminal::mv(const std::string& oldName, const std::string& newName) {
    auto dir = currentDir();
    auto entry = dir->findChild(oldName);
    if (!entry) {
        std::cout << "Entry not found.\n";
        return;
    }
    if (dir->findChild(newName)) {
        std::cout << "Target name already exists.\n";
        return;
    }
    entry->name = newName;
    std::cout << "Renamed.\n";
}

void Terminal::edit(const std::string& fileName) {
    auto dir = currentDir();
    auto entry = dir->findChild(fileName);
    if (!entry) {
        std::cout << "File not found.\n";
        return;
    }
    if (entry->asDirectory()) {
        std::cout << "Cannot edit a directory.\n";
        return;
    }

    // Если это PostponedFile, заменяем на реальный тип
    if (auto pf = std::dynamic_pointer_cast<PostponedFile>(entry)) {
        std::cout << "This file is not yet typed. Choose type: (s)ingle-line or (m)ulti-line: ";
        char type;
        std::cin >> type;
        std::cin.ignore();

        std::shared_ptr<Entry> newFile;
        if (type == 's') {
            newFile = std::make_shared<SingleLineFile>(entry->name);
        } else if (type == 'm') {
            newFile = std::make_shared<MultiLineFile>(entry->name);
        } else {
            std::cout << "Invalid type. File remains untyped.\n";
            return;
        }

        dir->removeChild(entry->name);
        dir->addChild(newFile);
        newFile->edit(); // сразу редактируем
    } else {
        entry->edit();
    }
}

std::string Terminal::getPrompt() {
    std::string prompt;
    for (size_t i = 1; i < path.size(); ++i) {
        prompt += path[i]->name + "/";
    }
    if (prompt.empty()) prompt = "/";
    return "[" + prompt + "]$ ";
}

void Terminal::run() {
    std::string line;
    std::cout << "Simple OOP Terminal. Type 'help' for commands.\n";
    while (true) {
        std::cout << getPrompt();
        std::getline(std::cin, line);
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "exit") {
            break;
        } else if (cmd == "help") {
            std::cout << "Commands:\n";
            std::cout << "  ls                - list visible entries\n";
            std::cout << "  ls -a             - list all entries (including hidden)\n";
            std::cout << "  cd <dir>          - change directory\n";
            std::cout << "  cat <file>        - show file content\n";
            std::cout << "  touch <file>      - create new empty file (type undefined)\n";
            std::cout << "  mkdir <dir>       - create directory\n";
            std::cout << "  rm <name>         - soft delete (hide)\n";
            std::cout << "  restore <name>    - restore hidden entry\n";
            std::cout << "  mv <old> <new>    - rename entry\n";
            std::cout << "  edit <file>       - edit file (polymorphic)\n";
            std::cout << "  help              - show this help\n";
            std::cout << "  exit              - quit\n";
        } else if (cmd == "ls") {
            std::string arg;
            iss >> arg;
            if (arg == "-a")
                listAllHidden();
            else
                list();
        } else if (cmd == "cd") {
            std::string dir;
            iss >> dir;
            if (dir.empty())
                std::cout << "Usage: cd <dir|..>\n";
            else
                cd(dir);
        } else if (cmd == "cat") {
            std::string file;
            iss >> file;
            if (file.empty())
                std::cout << "Usage: cat <file>\n";
            else
                cat(file);
        } else if (cmd == "touch") {
            std::string file;
            iss >> file;
            if (file.empty())
                std::cout << "Usage: touch <file>\n";
            else
                touch(file);
        } else if (cmd == "mkdir") {
            std::string dir;
            iss >> dir;
            if (dir.empty())
                std::cout << "Usage: mkdir <dir>\n";
            else
                mkdir(dir);
        } else if (cmd == "rm") {
            std::string name;
            iss >> name;
            if (name.empty())
                std::cout << "Usage: rm <name>\n";
            else
                rm(name);
        } else if (cmd == "restore") {
            std::string name;
            iss >> name;
            if (name.empty())
                std::cout << "Usage: restore <name> (without leading dot)\n";
            else
                restore(name);
        } else if (cmd == "mv") {
            std::string oldName, newName;
            iss >> oldName >> newName;
            if (oldName.empty() || newName.empty())
                std::cout << "Usage: mv <old> <new>\n";
            else
                mv(oldName, newName);
        } else if (cmd == "edit") {
            std::string file;
            iss >> file;
            if (file.empty())
                std::cout << "Usage: edit <file>\n";
            else
                edit(file);
        } else {
            std::cout << "Unknown command. Type 'help'.\n";
        }
    }
}
