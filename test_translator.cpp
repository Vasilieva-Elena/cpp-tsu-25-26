#include "Translator.h"
#include <sstream>
#include <cassert>
#include <iostream>

void testGenerateAndPrintAtoms() {
    Translator tr(std::cin);  // фиктивный поток, но нам нужен только вывод
    auto t1 = tr.allocTemp();
    auto t2 = tr.allocTemp();
    auto num = std::make_shared<NumberOperand>(42);
    
    auto atom = std::make_unique<BinaryOpAtom>("ADD", num, t1, t2);
    tr.generateAtom(std::move(atom));
    
    std::ostringstream oss;
    tr.printAtoms(oss);
    // Формат вывода зависит от toString() операндов. У нас числа в кавычках, индексы без.
    // t1 - первый временный, t2 - второй. Индексы 0 и 1.
    assert(oss.str() == "(ADD, '42', 0, 1)\n");
    std::cout << "testGenerateAndPrintAtoms passed\n";
}

void testAllocTemp() {
    SymbolTable st;
    auto t1 = st.alloc();
    auto t2 = st.alloc();
    auto t3 = st.add("x");
    
    assert(t1->toString() == "0");
    assert(t2->toString() == "1");
    assert(t3->toString() == "2");
    std::cout << "testAllocTemp passed\n";
}

void testNewLabel() {
    Translator tr(std::cin);
    auto l1 = tr.newLabel();
    auto l2 = tr.newLabel();
    assert(l1->toString() == "0");
    assert(l2->toString() == "1");
    std::cout << "testNewLabel passed\n";
}

void testErrors() {
    Translator tr(std::cin);
    bool caught = false;
    try {
        tr.syntaxError("test error");
    } catch (const TranslationException& e) {
        caught = true;
        assert(std::string(e.what()).find("test error") != std::string::npos);
    }
    assert(caught);
    
    caught = false;
    try {
        tr.lexicalError("lex error");
    } catch (const TranslationException& e) {
        caught = true;
        assert(std::string(e.what()).find("lex error") != std::string::npos);
    }
    assert(caught);
    std::cout << "testErrors passed\n";
}

int main() {
    testGenerateAndPrintAtoms();
    testAllocTemp();
    testNewLabel();
    testErrors();
    std::cout << "All Translator tests passed!\n";
    return 0;
}
