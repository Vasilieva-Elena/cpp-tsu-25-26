#pragma once

#include "Entry.h"
#include <vector>
#include <memory>

class Directory : public Entry {
    std::vector<std::shared_ptr<Entry>> children;

public:
    explicit Directory(const std::string& n);

    std::vector<std::shared_ptr<Entry>> listAll() const override;
    std::string displayName() const override;
    std::shared_ptr<Directory> asDirectory() override;
    void edit() override;
    void hide() override;
    void restore() override;

    void addChild(std::shared_ptr<Entry> child);
    std::shared_ptr<Entry> findChild(const std::string& childName);
    void removeChild(const std::string& childName);
    void renameChild(const std::string& oldName, const std::string& newName);
};
