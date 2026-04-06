#pragma once

#include "Entry.h"

class SingleLineFile : public Entry {
    std::string content;

public:
    SingleLineFile(const std::string& n, const std::string& c = "");

    std::string displayName() const override;
    void edit() override;
    void hide() override;
    void restore() override;
    std::string getContent() const override;
    void setContent(const std::string& c) override;
};
