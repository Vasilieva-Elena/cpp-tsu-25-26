#include "StringTable.h"
#include <algorithm>

const std::string& StringTable::operator[](int index) const {
    // Предполагаем, что индекс всегда корректен
    return _strings[index];
}

int StringTable::add(const std::string& name) {
    // Ищем, есть ли уже такое имя
    auto it = std::find(_strings.begin(), _strings.end(), name);
    if (it != _strings.end()) {
        // Нашли — возвращаем индекс
        return static_cast<int>(it - _strings.begin());
    }
    // Не нашли — добавляем в конец
    _strings.push_back(name);
    return static_cast<int>(_strings.size()) - 1;
}

std::ostream& operator<<(std::ostream& os, const StringTable& st) {
    for (size_t i = 0; i < st._strings.size(); ++i) {
        os << i << " " << st._strings[i] << std::endl;
    }
    return os;
}
