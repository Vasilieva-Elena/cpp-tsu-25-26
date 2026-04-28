#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "Scaner.h"
#include "SymbolTable.h"
#include "StringTable.h"
#include "Atoms.h"
#include <memory>
#include <vector>
#include <iostream>

// Исключение для ошибок трансляции
class TranslationException : public std::exception {
    std::string _message;
public:
    TranslationException(const std::string& msg) : _message(msg) {}
    const char* what() const noexcept override { return _message.c_str(); }
};

class Translator {
protected:
    std::vector<std::unique_ptr<Atom>> _atoms;   // хранилище атомов
    SymbolTable _symTable;                       // таблица символов
    StringTable _strTable;                       // таблица строк
    Scanner _scanner;                            // лексический анализатор
    Token _currentLexem;                         // текущий токен

    int _nextLabel;                              // счётчик для новых меток

    // Вспомогательные методы для работы с токенами
    void nextToken();                            // прочитать следующий токен
    void match(LexemType expected);              // проверить и пропустить токен

public:
    Translator(std::istream& input);

    // Добавление атома в список
    void generateAtom(std::unique_ptr<Atom> atom);
    
    // Вывод всех атомов в поток
    void printAtoms(std::ostream& stream) const;

    // Создание новой временной переменной (через SymbolTable::alloc)
    std::shared_ptr<MemoryOperand> allocTemp();

    // Создание новой метки
    std::shared_ptr<LabelOperand> newLabel();

    // Методы обработки ошибок (кидают исключения)
    void syntaxError(const std::string& message);
    void lexicalError(const std::string& message);

    // Основной метод для запуска трансляции (пока пустой заглушка)
    void translate();
};

#endif
