#include "Scaner.h"
#include <sstream>
#include <cassert>
#include <iostream>

using namespace std;

void test_constructor_lexemtype() {
    cout << "Тест конструктора LexemType -  ";
    Token t(LexemType::lpar);
    assert(t.type() == LexemType::lpar);
    ostringstream oss;
    t.print(oss);
    assert(oss.str() == "[lpar]");
    cout << "OK" << endl;
}

void test_constructor_int() {
    cout << "Тест конструктора int - ";
    Token t(42);
    assert(t.type() == LexemType::num);
    assert(t.value() == 42);
    ostringstream oss;
    t.print(oss);
    assert(oss.str() == "[num, 42]");
    cout << "OK" << endl;
}

void test_constructor_string() {
    cout << "Тест строкового конструктора - ";
    // тест для идентификатора
    Token t1(LexemType::id, "variable");
    assert(t1.type() == LexemType::id);
    assert(t1.str() == "variable");
    ostringstream oss1;
    t1.print(oss1);
    assert(oss1.str() == "[id, \"variable\"]");
    // тест для строки
    Token t2(LexemType::str, "hello world");
    assert(t2.type() == LexemType::str);
    assert(t2.str() == "hello world");
    ostringstream oss2;
    t2.print(oss2);
    assert(oss2.str() == "[str, \"hello world\"]");
    // тест для ошибки
    Token t3(LexemType::error, "unknown symbol");
    assert(t3.type() == LexemType::error);
    assert(t3.str() == "unknown symbol");
    ostringstream oss3;
    t3.print(oss3);
    assert(oss3.str() == "[error, \"unknown symbol\"]");
    cout << "OK" << endl;
}


void test_constructor_char() {
    cout << "Тест символьного конструктора -  ";
    Token t('A');
    assert(t.type() == LexemType::chr);
    assert(t.value() == 65); // ASCII код для 'A'
    ostringstream oss;
    t.print(oss);
    assert(oss.str() == "[chr, 'A']");
    cout << "OK" << endl;
}

// тесты вывода всех типов лексем
void test_all_lexem_types() {
    // Вывод сообщения о начале теста
    cout << "Тест вывода всех LexemType - ";
    // создание массива токенов всех типов (кроме тех, что требуют параметров)
    Token tokens[] = {
        Token(LexemType::lpar),
        Token(LexemType::rpar),
        Token(LexemType::lbrace),
        Token(LexemType::rbrace),
        Token(LexemType::lbracket),
        Token(LexemType::rbracket),
        Token(LexemType::semicolon),
        Token(LexemType::comma),
        Token(LexemType::colon),
        Token(LexemType::opassign),
        Token(LexemType::opplus),
        Token(LexemType::opminus),
        Token(LexemType::opmult),
        Token(LexemType::opinc),
        Token(LexemType::opeq),
        Token(LexemType::opne),
        Token(LexemType::oplt),
        Token(LexemType::opgt),
        Token(LexemType::ople),
        Token(LexemType::opnot),
        Token(LexemType::opor),
        Token(LexemType::opand),
        Token(LexemType::kwint),
        Token(LexemType::kwchar),
        Token(LexemType::kwif),
        Token(LexemType::kwelse),
        Token(LexemType::kwswitch),
        Token(LexemType::kwcase),
        Token(LexemType::kwwhile),
        Token(LexemType::kwfor),
        Token(LexemType::kwreturn),
        Token(LexemType::kwin),
        Token(LexemType::kwout),
        Token(LexemType::eof)
    };
    // массив ожидаемых выводов
    string expected[] = {
        "[lpar]",
        "[rpar]",
        "[lbrace]",
        "[rbrace]",
        "[lbracket]",
        "[rbracket]",
        "[semicolon]",
        "[comma]",
        "[colon]",
        "[opassign]",
        "[opplus]",
        "[opminus]",
        "[opmult]",
        "[opinc]",
        "[opeq]",
        "[opne]",
        "[oplt]",
        "[opgt]",
        "[ople]",
        "[opnot]",
        "[opor]",
        "[opand]",
        "[kwint]",
        "[kwchar]",
        "[kwif]",
        "[kwelse]",
        "[kwswitch]",
        "[kwcase]",
        "[kwwhile]",
        "[kwfor]",
        "[kwreturn]",
        "[kwin]",
        "[kwout]",
        "[eof]"
    };

    size_t tokens_count = sizeof(tokens) / sizeof(tokens[0]);

    for (size_t i = 0; i < tokens_count; i++) {
        ostringstream oss;
        // Вызов printа для текущего токена
        // Вывод не в консоль, а в oss
        tokens[i].print(oss);
        // строка из потока
        string actual_output = oss.str();
        assert(actual_output == expected[i]);
    }
    cout << "OK" << endl;
}

// тесты специальных случаи
void test_special_cases() {
    cout << "Тест специальны случаев -  ";
    // тест нулевого символа
    Token t3('\0');
    ostringstream oss3;
    t3.print(oss3);
    // тест отрицательного числа
    Token t4(-123);
    ostringstream oss4;
    t4.print(oss4);
    assert(oss4.str() == "[num, -123]");
    // тест пробельного символа
    Token t5(' ');
    ostringstream oss5;
    t5.print(oss5);
    assert(oss5.str() == "[chr, ' ']");
    cout << "OK" << endl;
}

// Тест методов доступа
void test_access_methods() {
    cout << "Тест методов доступа -  ";
    // Тут тест value() для не-числовых токенов
    Token t1(LexemType::lpar);
    assert(t1.value() == 0); // Должно быть 0 для не-числовых
    // Тут тест str() для не-строковых токенов
    Token t2(100);
    assert(t2.str() == ""); // Должно быть пусто для не-строковых
    cout << "OK" << endl;
}

int main() {
    cout << "Тесты класса Token:" << endl << endl;
    test_constructor_lexemtype();
    test_constructor_int();
    test_constructor_string();
    test_constructor_char();
    test_all_lexem_types();
    test_special_cases();
    test_access_methods();
    cout << endl << "Все тесты проходят)" << endl;
    return 0;
}
