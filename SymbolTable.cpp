#include "SymbolTable.h"
#include "Atoms.h"        // теперь нужно для MemoryOperand
#include <algorithm>

const SymbolTable::TableRecord& SymbolTable::operator[](int index) const {
    return _records[index];
}

std::shared_ptr<MemoryOperand> SymbolTable::add(const std::string& name) {
    // Ищем запись по имени
    auto it = std::find_if(_records.begin(), _records.end(),
        [&name](const TableRecord& rec) { return rec._name == name; });
    if (it != _records.end()) {
        int index = static_cast<int>(it - _records.begin());
        // Возвращаем уже созданный операнд (если он есть)
        if (index < static_cast<int>(_operands.size()) && _operands[index]) {
            return _operands[index];
        }
        // На всякий случай создаём, если вдруг не было
        auto operand = std::make_shared<MemoryOperand>(index, this);
        if (index >= static_cast<int>(_operands.size()))
            _operands.resize(index + 1);
        _operands[index] = operand;
        return operand;
    }
    // Новая запись
    int newIndex = static_cast<int>(_records.size());
    _records.push_back(TableRecord(name));
    auto operand = std::make_shared<MemoryOperand>(newIndex, this);
    _operands.push_back(operand);
    return operand;
}

std::ostream& operator<<(std::ostream& os, const SymbolTable& st) {
    for (size_t i = 0; i < st._records.size(); ++i) {
        os << i << " " << st._records[i]._name << std::endl;
    }
    return os;
}
