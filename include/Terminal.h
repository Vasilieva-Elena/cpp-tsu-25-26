#pragma once

#include <memory>
#include <vector>
#include <string>

class Directory;

class Terminal {
    std::shared_ptr<Directory> root;
    std::vector<std::shared_ptr<Directory>> path;

public:
    Terminal();
    void run();

private:
    std::shared_ptr<Directory> currentDir();
    void list();
    void listAllHidden();
    void cd(const std::string& dirName);
    void cat(const std::string& fileName);
    void touch(const std::string& fileName);
    void mkdir(const std::string& dirName);
    void rm(const std::string& name);
    void restore(const std::string& name);
    void mv(const std::string& oldName, const std::string& newName);
    void edit(const std::string& fileName);
    std::string getPrompt();
};
