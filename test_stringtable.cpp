#include "StringTable.h"
#include <cassert>
#include <iostream>

void testAddAndAccess() {
    StringTable st;
    
    int idx1 = st.add("a");
    int idx2 = st.add("b");
    int idx3 = st.add("a");  // повтор
    
    assert(idx1 == 0);
    assert(idx2 == 1);
    assert(idx3 == 0);       // вернулся старый индекс
    
    assert(st[0] == "a");
    assert(st[1] == "b");
    
    std::cout << "testAddAndAccess passed\n";
}

void testPrint() {
    StringTable st;
    st.add("x");
    st.add("y");
    st.add("temp1");
    
    std::ostringstream oss;
    oss << st;
    std::string expected = "0 x\n1 y\n2 temp1\n";
    assert(oss.str() == expected);
    
    std::cout << "testPrint passed\n";
}

int main() {
    testAddAndAccess();
    testPrint();
    std::cout << "All StringTable tests passed!\n";
    return 0;
}
