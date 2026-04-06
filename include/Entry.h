#pragma once

#include <memory>
#include <string>
#include <vector>

class Directory; // forward declaration

class Entry : public std::enable_shared_from_this<Entry> {
public:
    std::string name;
    bool hidden;

    explicit Entry(const std::string& n);
    virtual ~Entry() = default;

    virtual std::vector<std::shared_ptr<Entry>> listAll() const;
    virtual std::string displayName() const = 0;
    virtual std::shared_ptr<Directory> asDirectory();
    virtual void edit() = 0;
    virtual void hide() = 0;
    virtual void restore() = 0;
    virtual bool isHidden() const;
    virtual std::string getContent() const;
    virtual void setContent(const std::string& content);
};
