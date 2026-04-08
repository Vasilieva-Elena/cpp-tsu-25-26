#include "Scaner.h"
#include <sstream>
#include <cassert>
#include <iostream>

using namespace std;

// Тест 1: Проверка конструкторов и методов доступа
void testConstructorsAndAccessors() {
    cout << "=== Тест конструкторов и методов доступа ===" << endl;

    // Конструктор для лексем без значения
    Token token1(LexemType::lpar);
    assert(token1.type() == LexemType::lpar);
    assert(token1.value() == 0);
    assert(token1.str() == "");

    // Конструктор для чисел
    Token token2(123);
    assert(token2.type() == LexemType::num);
    assert(token2.value() == 123);
    assert(token2.str() == "");

    // Конструктор для идентификаторов
    Token token3(LexemType::id, "variable");
    assert(token3.type() == LexemType::id);
    assert(token3.value() == 0);
    assert(token3.str() == "variable");

    // Конструктор для символов
    Token token4('X');
    assert(token4.type() == LexemType::chr);
    assert(token4.value() == 88); // ASCII код 'X'
    assert(token4.str() == "");

    // Конструктор для строк
    Token token5(LexemType::str, "Hello World");
    assert(token5.type() == LexemType::str);
    assert(token5.value() == 0);
    assert(token5.str() == "Hello World");

    // Конструктор для ошибок
    Token token6(LexemType::error, "unknown symbol");
    assert(token6.type() == LexemType::error);
    assert(token6.value() == 0);
    assert(token6.str() == "unknown symbol");

    cout << " Все конструкторы и методы доступа работают правильно!" << endl;
}

// Тест 2: Проверка вывода для всех типов лексем
void testPrintAllLexemTypes() {
    cout << "\n=== Тест вывода всех типов лексем ===" << endl;

    // Используем ostringstream для перехвата вывода
    ostringstream stream;

    // Тесты для всех типов лексем без значений
    struct LexemTest {
        LexemType type;
        string expected;
    };

    LexemTest tests[] = {
        {LexemType::lpar, "[lpar]"},
        {LexemType::rpar, "[rpar]"},
        {LexemType::lbrace, "[lbrace]"},
        {LexemType::rbrace, "[rbrace]"},
        {LexemType::lbracket, "[lbracket]"},
        {LexemType::rbracket, "[rbracket]"},
        {LexemType::semicolon, "[semicolon]"},
        {LexemType::comma, "[comma]"},
        {LexemType::colon, "[colon]"},
        {LexemType::opassign, "[opassign]"},
        {LexemType::opplus, "[opplus]"},
        {LexemType::opminus, "[opminus]"},
        {LexemType::opmult, "[opmult]"},
        {LexemType::opinc, "[opinc]"},
        {LexemType::opeq, "[opeq]"},
        {LexemType::opne, "[opne]"},
        {LexemType::oplt, "[oplt]"},
        {LexemType::opgt, "[opgt]"},
        {LexemType::ople, "[ople]"},
        {LexemType::opnot, "[opnot]"},
        {LexemType::opor, "[opor]"},
        {LexemType::opand, "[opand]"},
        {LexemType::kwint, "[kwint]"},
        {LexemType::kwchar, "[kwchar]"},
        {LexemType::kwif, "[kwif]"},
        {LexemType::kwelse, "[kwelse]"},
        {LexemType::kwswitch, "[kwswitch]"},
        {LexemType::kwcase, "[kwcase]"},
        {LexemType::kwwhile, "[kwwhile]"},
        {LexemType::kwfor, "[kwfor]"},
        {LexemType::kwreturn, "[kwreturn]"},
        {LexemType::kwin, "[kwin]"},
        {LexemType::kwout, "[kwout]"},
        {LexemType::eof, "[eof]"}
    };

    for (const auto& test : tests) {
        Token token(test.type);
        stream.str(""); // Очистка потока
        token.print(stream);
        assert(stream.str() == test.expected);
        cout << " " << stream.str() << endl;
    }

    cout << " Все типы лексем без значений выводятся правильно!" << endl;
}

// Тест 3: Проверка вывода лексем со значениями
void testPrintWithValues() {
    cout << "\n=== Тест вывода лексем со значениями ===" << endl;

    ostringstream stream;

    // Тест числовых токенов
    Token num_token(42);
    stream.str("");
    num_token.print(stream);
    assert(stream.str() == "[num, 42]");
    cout << " " << stream.str() << endl;

    Token num_token2(-100);
    stream.str("");
    num_token2.print(stream);
    assert(stream.str() == "[num, -100]");
    cout << "✅ " << stream.str() << endl;

    // Тест символьных токенов
    Token chr_token('a');
    stream.str("");
    chr_token.print(stream);
    assert(stream.str() == "[chr, 'a']");
    cout << " " << stream.str() << endl;

    // Тест идентификаторов
    Token id_token(LexemType::id, "myVariable123");
    stream.str("");
    id_token.print(stream);
    assert(stream.str() == "[id, \"myVariable123\"]");
    cout << " " << stream.str() << endl;

    // Тест строк
    Token str_token(LexemType::str, "Hello World");
    stream.str("");
    str_token.print(stream);
    assert(stream.str() == "[str, \"Hello World\"]");
    cout << " " << stream.str() << endl;

    // Тест ошибок
    Token error_token(LexemType::error, "unexpected character '#'");
    stream.str("");
    error_token.print(stream);
    assert(stream.str() == "[error, \"unexpected character '#'\"]");
    cout << " " << stream.str() << endl;

    cout << " Все лексемы со значениями выводятся правильно!" << endl;
}

// Тест 4: Граничные случаи
void testEdgeCases() {
    cout << "\n=== Тест граничных случаев ===" << endl;

    ostringstream stream;

    // Пустой идентификатор
    Token empty_id(LexemType::id, "");
    stream.str("");
    empty_id.print(stream);
    assert(stream.str() == "[id, \"\"]");
    cout << " Пустой идентификатор: " << stream.str() << endl;

    // Пустая строка
    Token empty_str(LexemType::str, "");
    stream.str("");
    empty_str.print(stream);
    assert(stream.str() == "[str, \"\"]");
    cout << " Пустая строка: " << stream.str() << endl;

    // Число 0
    Token zero_num(0);
    stream.str("");
    zero_num.print(stream);
    assert(stream.str() == "[num, 0]");
    cout << " Число 0: " << stream.str() << endl;

    // Символ с кодом 0 - особый случай, проверяем отдельно
    Token null_char('\0');
    stream.str("");
    null_char.print(stream);
    // Для нулевого символа проверяем, что тип правильный и вывод не пустой
    assert(null_char.type() == LexemType::chr);
    assert(null_char.value() == 0);
    assert(!stream.str().empty());
    assert(stream.str().find("[chr,") != string::npos);
    cout << " Символ \\0: " << stream.str() << endl;

    // Простая строка для теста
    Token simple_str(LexemType::str, "Test");
    stream.str("");
    simple_str.print(stream);
    assert(simple_str.type() == LexemType::str);
    assert(simple_str.str() == "Test");
    assert(!stream.str().empty());
    cout << " Простая строка: " << stream.str() << endl;

    cout << " Все граничные случаи обрабатываются правильно!" << endl;
}

// Главная функция тестов
int main() {
    cout << " ЗАПУСК ПОЛНЫХ ТЕСТОВ ДЛЯ КЛАССА TOKEN" << endl;
    cout << "=========================================" << endl;

    try {
        testConstructorsAndAccessors();
        testPrintAllLexemTypes();
        testPrintWithValues();
        testEdgeCases();

        cout << "\n ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << endl;
        cout << " Класс Token готов к использованию в лексическом анализаторе." << endl;

    } catch (const exception& e) {
        cout << " ОШИБКА В ТЕСТАХ: " << e.what() << endl;
        return 1;
    }

    return 0;
}
