#include "SymbolTable.h"
#include <cassert>
#include <iostream>
#include <sstream>

void testAddAndAccess() {
    SymbolTable st;
    
    int idx1 = st.add("a");
    int idx2 = st.add("b");
    int idx3 = st.add("a");  // повтор
    
    assert(idx1 == 0);
    assert(idx2 == 1);
    assert(idx3 == 0);       // вернулся старый индекс
    
    assert(st[0]._name == "a");
    assert(st[1]._name == "b");
    
    std::cout << "testAddAndAccess passed\n";
}

void testPrint() {
    SymbolTable st;
    st.add("x");
    st.add("y");
    st.add("temp1");
    
    std::ostringstream oss;
    oss << st;
    std::string expected = "0 x\n1 y\n2 temp1\n";
    assert(oss.str() == expected);
    
    std::cout << "testPrint passed\n";
}

void testTableRecordComparison() {
    SymbolTable::TableRecord r1("var");
    SymbolTable::TableRecord r2("var");
    SymbolTable::TableRecord r3("other");
    
    assert(r1 == r2);
    assert(!(r1 == r3));
    
    std::cout << "testTableRecordComparison passed\n";
}

int main() {
    testAddAndAccess();
    testPrint();
    testTableRecordComparison();
    std::cout << "All SymbolTable tests passed!\n";
    return 0;
}
