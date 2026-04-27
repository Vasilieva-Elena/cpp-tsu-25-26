#include "Atoms.h"
#include "StringTable.h"
#include "SymbolTable.h"
#include <sstream>

// NumberOperand
NumberOperand::NumberOperand(int value) : _value(value) {}

std::string NumberOperand::toString() const {
    return "'" + std::to_string(_value) + "'";
}

// MemoryOperand
MemoryOperand::MemoryOperand(int index, const SymbolTable* symbolTable)
    : _index(index), _symbolTable(symbolTable) {}

std::string MemoryOperand::toString() const {
    return std::to_string(_index);
}

bool MemoryOperand::operator==(const MemoryOperand& other) const {
    return _index == other._index && _symbolTable == other._symbolTable;
}

// StringOperand
StringOperand::StringOperand(int index, const StringTable* stringTable)
    : _index(index), _stringTable(stringTable) {}

std::string StringOperand::toString() const {
    return std::to_string(_index);
}

bool StringOperand::operator==(const StringOperand& other) const {
    return _index == other._index && _stringTable == other._stringTable;
}

// LabelOperand
LabelOperand::LabelOperand(int labelID) : _labelID(labelID) {}

std::string LabelOperand::toString() const {
    return std::to_string(_labelID);
}
