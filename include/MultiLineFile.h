#pragma once

#include "Entry.h"
#include <vector>

class MultiLineFile : public Entry {
    std::vector<std::string> lines;

public:
    MultiLineFile(const std::string& n, const std::vector<std::string>& l = {});

    std::string displayName() const override;
    void edit() override;
    void hide() override;
    void restore() override;
    std::string getContent() const override;
    void setContent(const std::vector<std::string>& l);
};
