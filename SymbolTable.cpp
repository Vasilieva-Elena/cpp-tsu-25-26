#include "SymbolTable.h"
#include <algorithm>

const SymbolTable::TableRecord& SymbolTable::operator[](int index) const {
    return _records[index];
}

int SymbolTable::add(const std::string& name) {
    // Ищем, есть ли уже запись с таким именем
    auto it = std::find_if(_records.begin(), _records.end(),
        [&name](const TableRecord& rec) { return rec._name == name; });
    if (it != _records.end()) {
        // Нашли — возвращаем индекс
        return static_cast<int>(it - _records.begin());
    }
    // Не нашли — добавляем новую запись
    _records.push_back(TableRecord(name));
    return static_cast<int>(_records.size()) - 1;
}

std::ostream& operator<<(std::ostream& os, const SymbolTable& st) {
    for (size_t i = 0; i < st._records.size(); ++i) {
        os << i << " " << st._records[i]._name << std::endl;
    }
    return os;
}
