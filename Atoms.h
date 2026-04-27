#ifndef ATOMS_H
#define ATOMS_H

#include <string>
#include <memory>

class StringTable;
class SymbolTable;

class Operand {
public:
    virtual ~Operand() = default;
    virtual std::string toString() const = 0;
};

class RValue : public Operand {
public:
    virtual ~RValue() = default;
};

class NumberOperand : public RValue {
    int _value;
public:
    NumberOperand(int value);
    std::string toString() const override;
};

class MemoryOperand : public RValue {
    int _index;
    const SymbolTable* _symbolTable;
public:
    MemoryOperand(int index, const SymbolTable* symbolTable);
    std::string toString() const override;
    
    // Добавленный оператор сравнения
    bool operator==(const MemoryOperand& other) const;
};

class StringOperand : public Operand {
    int _index;
    const StringTable* _stringTable;
public:
    StringOperand(int index, const StringTable* stringTable);
    std::string toString() const override;
    
    // Добавленный оператор сравнения
    bool operator==(const StringOperand& other) const;
};

class LabelOperand : public Operand {
    int _labelID;
public:
    LabelOperand(int labelID);
    std::string toString() const override;
};

#endif
