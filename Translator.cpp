#include "Translator.h"
#include <sstream>

Translator::Translator(std::istream& input)
    : _scanner(input), _nextLabel(0) {
    nextToken();  // загружаем первый токен
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
        oss << "Ожидался токен типа " << static_cast<int>(expected)
            << ", получен " << static_cast<int>(_currentLexem.type());
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
    static int tempCounter = 0;
    std::string tempName = "temp" + std::to_string(++tempCounter);
    return _symTable.add(tempName);
}

std::shared_ptr<LabelOperand> Translator::newLabel() {
    return std::make_shared<LabelOperand>(_nextLabel++);
}

void Translator::syntaxError(const std::string& message) {
    throw TranslationException("Синтаксическая ошибка: " + message);
}

void Translator::lexicalError(const std::string& message) {
    throw TranslationException("Лексическая ошибка: " + message);
}

void Translator::translate() {
    // Пока ничего не делаем — заглушка. В следующем этапе добавим разбор выражений.
    // Например, просто считываем все токены до конца файла.
    while (_currentLexem.type() != LexemType::eof) {
        nextToken();
    }
}
