#include "Entry.h"
#include "Directory.h"

Entry::Entry(const std::string& n) : name(n), hidden(false) {}

std::vector<std::shared_ptr<Entry>> Entry::listAll() const {
    return {};
}

std::shared_ptr<Directory> Entry::asDirectory() {
    return nullptr;
}

bool Entry::isHidden() const {
    return hidden;
}

std::string Entry::getContent() const {
    return "";
}

void Entry::setContent(const std::string&) {}
