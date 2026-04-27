#include "SymbolTable.h"
#include "Atoms.h"
#include <cassert>
#include <iostream>

int main() {
    SymbolTable st;
    
    auto op1 = st.add("x");    // первый вызов, создаётся новая запись
    auto op2 = st.add("x");    // повтор, должен вернуть тот же операнд
    auto op3 = st.add("y");    // новая запись
    
    // Проверяем, что объекты операндов одинаковы для "x"
    assert(op1 == op2);
    // Для разных имён — разные операнды
    assert(op1 != op3);
    
    // Проверяем индексы (toString() возвращает индекс)
    assert(op1->toString() == "0");
    assert(op3->toString() == "1");
    
    // Дополнительно проверим, что в таблице действительно две записи
    std::cout << st << std::endl;
    
    std::cout << "SymbolTable test passed\n";
    return 0;
}
