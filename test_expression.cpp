#include "Translator.h"
#include <sstream>
#include <iostream>

int main() {
    std::string input = "a + b * c - 5";
    std::istringstream iss(input);
    Translator tr(iss);
    tr.translate();
    return 0;
}
