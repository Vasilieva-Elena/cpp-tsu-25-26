#ifndef ATOMS_H
#define ATOMS_H

#include <string>

// Предварительные объявления таблиц (чтобы избежать циклической зависимости)
class StringTable;
class SymbolTable;

// Базовый класс для всех операндов
class Operand {
public:
    virtual ~Operand() = default;
    virtual std::string toString() const = 0;
};

// Операнды, которые могут использоваться в вычислениях (RValue)
class RValue : public Operand {
public:
    virtual ~RValue() = default;
    // Не добавляет новых методов, только метка-интерфейс
};

// Операнд-число (константа)
class NumberOperand : public RValue {
    int _value;
public:
    NumberOperand(int value);
    std::string toString() const override;
};

// Операнд-переменная (ссылка на таблицу символов)
class MemoryOperand : public RValue {
    int _index;
    const SymbolTable* _symbolTable;
public:
    MemoryOperand(int index, const SymbolTable* symbolTable);
    std::string toString() const override;
};

// Операнд-строка (ссылка на таблицу строк)
class StringOperand : public Operand {
    int _index;
    const StringTable* _stringTable;
public:
    StringOperand(int index, const StringTable* stringTable);
    std::string toString() const override;
};

// Операнд-метка (для переходов, в этом задании не используется, но по иерархии нужен)
class LabelOperand : public Operand {
    int _labelID;
public:
    LabelOperand(int labelID);
    std::string toString() const override;
};

#endif
