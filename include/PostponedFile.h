#pragma once

#include "Entry.h"

class PostponedFile : public Entry {
public:
    explicit PostponedFile(const std::string& n);

    std::string displayName() const override;
    void edit() override;
    void hide() override;
    void restore() override;
    std::string getContent() const override;
    void setContent(const std::string& c) override;
};
