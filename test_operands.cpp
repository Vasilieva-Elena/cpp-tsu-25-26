#include "Atoms.h"
#include "StringTable.h"
#include "SymbolTable.h"
#include <cassert>
#include <iostream>
#include <sstream>

int main() {
    // Создадим реальные таблицы (они уже реализованы)
    StringTable strTable;
    SymbolTable symTable;

    // Добавим несколько строк в таблицы для проверки
    int idxStr = strTable.add("Hello");
    int idxVar = symTable.add("myVar");
    int idxTemp = symTable.add("temp1");

    // --- NumberOperand ---
    NumberOperand numOp(42);
    assert(numOp.toString() == "'42'");
    std::cout << "NumberOperand: " << numOp.toString() << std::endl;

    // --- MemoryOperand ---
    MemoryOperand memOp(idxVar, &symTable);
    // Ожидаем, что toString() вернёт индекс (0, так как первый добавленный символ)
    assert(memOp.toString() == "0");
    std::cout << "MemoryOperand (var): " << memOp.toString() << std::endl;

    MemoryOperand memOp2(idxTemp, &symTable);
    assert(memOp2.toString() == "1");
    std::cout << "MemoryOperand (temp): " << memOp2.toString() << std::endl;

    // --- StringOperand ---
    StringOperand strOp(idxStr, &strTable);
    assert(strOp.toString() == "0");
    std::cout << "StringOperand: " << strOp.toString() << std::endl;

    // --- LabelOperand ---
    LabelOperand labelOp(100);
    assert(labelOp.toString() == "100");
    std::cout << "LabelOperand: " << labelOp.toString() << std::endl;

    // Проверка наследования: RValue должен быть подтипом Operand
    RValue* rv = new NumberOperand(5);
    assert(dynamic_cast<Operand*>(rv) != nullptr);
    delete rv;

    std::cout << "All tests passed!\n";
    return 0;
}
