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
