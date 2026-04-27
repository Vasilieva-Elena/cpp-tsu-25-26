#include "StringTable.h"
#include "Atoms.h"
#include <cassert>
#include <iostream>

int main() {
    StringTable st;
    
    auto op1 = st.add("Hello");
    auto op2 = st.add("Hello");
    auto op3 = st.add("World");
    
    assert(op1 == op2);
    assert(op1 != op3);
    
    assert(op1->toString() == "0");
    assert(op3->toString() == "1");
    
    std::cout << st << std::endl;
    
    std::cout << "StringTable test passed\n";
    return 0;
}
