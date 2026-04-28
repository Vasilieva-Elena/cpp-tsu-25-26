#include "Translator.h"
#include <sstream>

Translator::Translator(std::istream& input)
    : _scanner(input), _currentLexem(LexemType::eof), _nextLabel(0) {
    nextToken();
}

void Translator::nextToken() {
    _currentLexem = _scanner.getNextToken();
    if (_currentLexem.type() == LexemType::error) {
        lexicalError(_currentLexem.str());
    }
}

void Translator::match(LexemType expected) {
    if (_currentLexem.type() == expected) {
        nextToken();
    } else {
        std::ostringstream oss;
        oss << "Expected token type " << static_cast<int>(expected)
            << ", got " << static_cast<int>(_currentLexem.type());
        syntaxError(oss.str());
    }
}

void Translator::generateAtom(std::unique_ptr<Atom> atom) {
    _atoms.push_back(std::move(atom));
}

void Translator::printAtoms(std::ostream& stream) const {
    for (const auto& atom : _atoms) {
        stream << atom->toString() << std::endl;
    }
}

std::shared_ptr<MemoryOperand> Translator::allocTemp() {
    return _symTable.alloc();
}

std::shared_ptr<LabelOperand> Translator::newLabel() {
    return std::make_shared<LabelOperand>(_nextLabel++);
}

void Translator::syntaxError(const std::string& message) {
    throw TranslationException("Syntax error: " + message);
}

void Translator::lexicalError(const std::string& message) {
    throw TranslationException("Lexical error: " + message);
}

void Translator::translate() {
    // Заглушка – пока просто читаем все токены до конца файла
    while (_currentLexem.type() != LexemType::eof) {
        nextToken();
    }
}

// ========== Рекурсивный спуск для выражений ==========

std::shared_ptr<RValue> Translator::E() {
    return E7();   // правило 1
}

std::shared_ptr<RValue> Translator::E7() {
    auto q = E6();
    if (!q) syntaxError("E6 failed in E7");
    auto p = E7_(q);
    if (!p) syntaxError("E7_ failed");
    return p;
}

std::shared_ptr<RValue> Translator::E7_(std::shared_ptr<RValue> p) {
    // правило 3: || E6 E7'
    if (_currentLexem.type() == LexemType::opor) {
        nextToken();  // прочитали ||
        auto r = E6();
        if (!r) syntaxError("Expected E6 after ||");
        auto s = allocTemp();   // s = alloc(C)
        generateAtom(std::make_unique<BinaryOpAtom>("OR", p, r, s));
        auto q = E7_(s);
        if (!q) syntaxError("E7_ after OR failed");
        return q;
    }
    // правило 4: ε
    return p;
}

std::shared_ptr<RValue> Translator::E6() {
    auto q = E5();
    if (!q) syntaxError("E5 failed in E6");
    auto p = E6_(q);
    if (!p) syntaxError("E6_ failed");
    return p;
}

std::shared_ptr<RValue> Translator::E6_(std::shared_ptr<RValue> p) {
    // правило 6: && E5 E6'
    if (_currentLexem.type() == LexemType::opand) {
        nextToken();
        auto r = E5();
        if (!r) syntaxError("Expected E5 after &&");
        auto s = allocTemp();
        generateAtom(std::make_unique<BinaryOpAtom>("AND", p, r, s));
        auto q = E6_(s);
        if (!q) syntaxError("E6_ after AND failed");
        return q;
    }
    // правило 7: ε
    return p;
}

std::shared_ptr<RValue> Translator::E5() {
    auto q = E4();
    if (!q) syntaxError("E4 failed in E5");
    auto p = E5_(q);
    if (!p) syntaxError("E5_ failed");
    return p;
}

std::shared_ptr<RValue> Translator::E5_(std::shared_ptr<RValue> p) {
    LexemType op = _currentLexem.type();
    // правила 9-14: ==, !=, >, <, <=, >=
    if (op == LexemType::opeq || op == LexemType::opne ||
        op == LexemType::opgt || op == LexemType::oplt ||
        op == LexemType::ople || op == LexemType::opge) {
        nextToken();
        auto r = E4();
        if (!r) syntaxError("Expected E4 after relational operator");
        auto s = allocTemp();          // временная для результата сравнения (0 или 1)
        auto l = newLabel();           // метка для else-ветки
        // Сначала считаем, что результат = 1, затем если условие ложно, прыгаем на l и ставим 0
        generateAtom(std::make_unique<BinaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), nullptr, s));
        std::string cond;
        switch (op) {
            case LexemType::opeq: cond = "EQ"; break;
            case LexemType::opne: cond = "NE"; break;
            case LexemType::opgt: cond = "GT"; break;
            case LexemType::oplt: cond = "LT"; break;
            case LexemType::ople: cond = "LE"; break;
            case LexemType::opge: cond = "GE"; break;
            default: break;
        }
        generateAtom(std::make_unique<ConditionalJumpAtom>(cond, p, r, l));
        generateAtom(std::make_unique<BinaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), nullptr, s));
        generateAtom(std::make_unique<LabelOperand>(l->toString())); 
        auto q = E5_(s);
        if (!q) syntaxError("E5_ after comparison failed");
        return q;
    }
    // правило 14: ε
    return p;
}

std::shared_ptr<RValue> Translator::E4() {
    auto q = E3();
    if (!q) syntaxError("E3 failed in E4");
    auto p = E4_(q);
    if (!p) syntaxError("E4_ failed");
    return p;
}

std::shared_ptr<RValue> Translator::E4_(std::shared_ptr<RValue> p) {
    LexemType op = _currentLexem.type();
    if (op == LexemType::opplus || op == LexemType::opminus) {
        nextToken();
        auto r = E3();
        if (!r) syntaxError("Expected E3 after +/-");
        auto s = allocTemp();
        std::string atomOp = (op == LexemType::opplus) ? "ADD" : "SUB";
        generateAtom(std::make_unique<BinaryOpAtom>(atomOp, p, r, s));
        auto q = E4_(s);
        if (!q) syntaxError("E4_ after +/- failed");
        return q;
    }
    return p;
}

std::shared_ptr<RValue> Translator::E3() {
    auto q = E2();
    if (!q) syntaxError("E2 failed in E3");
    auto p = E3_(q);
    if (!p) syntaxError("E3_ failed");
    return p;
}

std::shared_ptr<RValue> Translator::E3_(std::shared_ptr<RValue> p) {
    if (_currentLexem.type() == LexemType::opmult) {
        nextToken();
        auto r = E2();
        if (!r) syntaxError("Expected E2 after *");
        auto s = allocTemp();
        generateAtom(std::make_unique<BinaryOpAtom>("MUL", p, r, s));
        auto q = E3_(s);
        if (!q) syntaxError("E3_ after * failed");
        return q;
    }
    return p;
}

std::shared_ptr<RValue> Translator::E2() {
    // правило 22: ! E1
    if (_currentLexem.type() == LexemType::opnot) {
        nextToken();
        auto q = E1();
        if (!q) syntaxError("Expected E1 after !");
        auto r = allocTemp();
        generateAtom(std::make_unique<UnaryOpAtom>("NOT", q, r));
        return r;
    }
    // правило 23: E1
    return E1();
}

std::shared_ptr<RValue> Translator::E1() {
    // правило 25: num
    if (_currentLexem.type() == LexemType::num) {
        int val = _currentLexem.value();
        nextToken();
        return std::make_shared<NumberOperand>(val);
    }
    // правило 26: chr
    if (_currentLexem.type() == LexemType::chr) {
        char ch = static_cast<char>(_currentLexem.value());
        nextToken();
        return std::make_shared<NumberOperand>(ch);   // символ как число
    }
    // правило 27: ++ id
    if (_currentLexem.type() == LexemType::opinc) {
        nextToken();
        if (_currentLexem.type() != LexemType::id)
            syntaxError("Expected id after ++");
        std::string name = _currentLexem.str();
        nextToken();
        auto q = _symTable.add(name);   // MemoryOperand для id
        auto r = allocTemp();           // временная для результата (новое значение)
        // {ADD} q 1 r
        generateAtom(std::make_unique<BinaryOpAtom>("ADD", q, std::make_shared<NumberOperand>(1), r));
        // p = q? В правиле 27: p = q, но q - это q (старое значение?) Согласно грамматике: {ADD}q1q, где первый q - переменная, второй q - результат. Но у нас r - результат ADD. Возвращаем r.
        return r;
    }
    // правило 28: id E1'
    if (_currentLexem.type() == LexemType::id) {
        std::string name = _currentLexem.str();
        nextToken();
        auto p = _symTable.add(name);
        auto q = E1_(p);
        if (!q) syntaxError("E1_ failed");
        return q;
    }
    // правило 24: ( E )
    if (_currentLexem.type() == LexemType::lpar) {
        nextToken();
        auto q = E();
        if (!q) syntaxError("Expression expected after '('");
        if (_currentLexem.type() != LexemType::rpar)
            syntaxError("Missing ')'");
        nextToken();
        return q;
    }
    syntaxError("Unexpected token in E1");
    return nullptr;
}

std::shared_ptr<RValue> Translator::E1_(std::shared_ptr<RValue> p) {
    // правило 29: ++   (постфиксный инкремент)
    if (_currentLexem.type() == LexemType::opinc) {
        nextToken();
        // s = checkVar(C,p)   – здесь p уже является MemoryOperand (id)
        auto s = p;   // просто используем p
        auto r = allocTemp();                    // временная для старого значения
        // {MOV} s ,, r  – копируем старое значение в r
        generateAtom(std::make_unique<UnaryOpAtom>("MOV", s, r));
        // {ADD} s 1 s  – увеличиваем s на 1
        generateAtom(std::make_unique<BinaryOpAtom>("ADD", s, std::make_shared<NumberOperand>(1), s));
        // q = r  – возвращаем старое значение
        return r;
    }
    // правило 31: ε (просто id без ++)
    return p;
}
