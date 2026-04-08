#include "Atoms.h"
#include "StringTable.h"
#include "SymbolTable.h"
#include <sstream>

// NumberOperand
NumberOperand::NumberOperand(int value) : _value(value) {}

std::string NumberOperand::toString() const {
    // Согласно примеру в задании: числа выводятся в кавычках, например '4'
    // Или можно просто как число. Выберем формат с кавычками, как в примере.
    return "'" + std::to_string(_value) + "'";
}

// MemoryOperand
MemoryOperand::MemoryOperand(int index, const SymbolTable* symbolTable)
    : _index(index), _symbolTable(symbolTable) {}

std::string MemoryOperand::toString() const {
    // Выводим индекс записи в таблице символов (как в примере: просто число)
    // Можно также добавить имя для отладки, но по заданию достаточно индекса.
    return std::to_string(_index);
}

// StringOperand
StringOperand::StringOperand(int index, const StringTable* stringTable)
    : _index(index), _stringTable(stringTable) {}

std::string StringOperand::toString() const {
    // Для строкового операнда выводим индекс в таблице строк (тоже число)
    return std::to_string(_index);
}

// LabelOperand
LabelOperand::LabelOperand(int labelID) : _labelID(labelID) {}

std::string LabelOperand::toString() const {
    return std::to_string(_labelID);
}
