#include "Directory.h"
#include <algorithm>
#include <iostream>

Directory::Directory(const std::string& n) : Entry(n) {}

std::vector<std::shared_ptr<Entry>> Directory::listAll() const {
    return children;
}

std::string Directory::displayName() const {
    return name + "/";
}

std::shared_ptr<Directory> Directory::asDirectory() {
    return std::dynamic_pointer_cast<Directory>(shared_from_this());
}

void Directory::edit() {
    std::cout << "Cannot edit a directory.\n";
}

void Directory::hide() {
    if (!hidden) {
        hidden = true;
        if (name[0] != '.') name = "." + name;
        for (auto& child : children) {
            child->hide();
        }
    }
}

void Directory::restore() {
    if (hidden) {
        hidden = false;
        if (name[0] == '.') name = name.substr(1);
        for (auto& child : children) {
            child->restore();
        }
    }
}

void Directory::addChild(std::shared_ptr<Entry> child) {
    children.push_back(std::move(child));
}

std::shared_ptr<Entry> Directory::findChild(const std::string& childName) {
    auto it = std::find_if(children.begin(), children.end(),
        [&childName](const std::shared_ptr<Entry>& e) {
            return e->name == childName;
        });
    return it != children.end() ? *it : nullptr;
}

void Directory::removeChild(const std::string& childName) {
    children.erase(std::remove_if(children.begin(), children.end(),
        [&childName](const std::shared_ptr<Entry>& e) {
            return e->name == childName;
        }), children.end());
}

void Directory::renameChild(const std::string& oldName, const std::string& newName) {
    auto child = findChild(oldName);
    if (child) child->name = newName;
}
