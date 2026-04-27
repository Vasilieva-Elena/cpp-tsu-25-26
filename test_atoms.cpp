#include "Atoms.h"
#include "SymbolTable.h"
#include <cassert>
#include <iostream>
#include <sstream>

int main() {
    SymbolTable symTab;
    auto temp1 = symTab.add("temp1");
    auto temp2 = symTab.add("temp2");
    
    auto left = std::make_shared<NumberOperand>(42);
    auto right = std::make_shared<MemoryOperand>(0, &symTab);
    auto label = std::make_shared<LabelOperand>(5);
    
    // BinaryOpAtom
    BinaryOpAtom addAtom("ADD", left, right, temp1);
    assert(addAtom.toString() == "(ADD, '42', 0, 0)");
    std::cout << addAtom.toString() << std::endl;
    
    // UnaryOpAtom
    UnaryOpAtom negAtom("NEG", right, temp2);
    assert(negAtom.toString() == "(NEG, 0, 1)");
    std::cout << negAtom.toString() << std::endl;
    
    // ConditionalJumpAtom
    ConditionalJumpAtom eqAtom("EQ", left, right, label);
    assert(eqAtom.toString() == "(EQ, '42', 0, 5)");
    std::cout << eqAtom.toString() << std::endl;
    
    // JumpAtom
    JumpAtom jmpAtom(label);
    assert(jmpAtom.toString() == "(JMP, 5)");
    std::cout << jmpAtom.toString() << std::endl;
    
    // OutAtom
    OutAtom outAtom(right);
    assert(outAtom.toString() == "(OUT, 0)");
    std::cout << outAtom.toString() << std::endl;
    
    std::cout << "\nAll Atom tests passed!\n";
    return 0;
}
