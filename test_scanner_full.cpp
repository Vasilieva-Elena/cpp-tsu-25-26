#include "Scaner.h"
#include <sstream>
#include <cassert>
#include <iostream>

using namespace std;

void testEmptyInput() {
    cout << " Тест пустого ввода " << endl;
    istringstream input("");
    Scanner scanner(input);

    Token token = scanner.getNextToken();
    assert(token.type() == LexemType::eof);
    cout << " Пустой ввод -> [eof]" << endl;
}

void testNumbers() {
    cout << " Тест чисел " << endl;
    istringstream input("123 456 0");
    Scanner scanner(input);

    Token token1 = scanner.getNextToken();
    assert(token1.type() == LexemType::num);
    assert(token1.value() == 123);
    cout << " Число 123: "; token1.print(cout); cout << endl;

    Token token2 = scanner.getNextToken();
    assert(token2.type() == LexemType::num);
    assert(token2.value() == 456);
    cout << " Число 456: "; token2.print(cout); cout << endl;

    Token token3 = scanner.getNextToken();
    assert(token3.type() == LexemType::num);
    assert(token3.value() == 0);
    cout << " Число 0: "; token3.print(cout); cout << endl;
}

void testIdentifiersAndKeywords() {
    cout << " Тест идентификаторов и ключевых слов " << endl;
    istringstream input("int main return x my_var123");
    Scanner scanner(input);

    Token token1 = scanner.getNextToken();
    assert(token1.type() == LexemType::kwint);
    cout << " Ключевое слово 'int': "; token1.print(cout); cout << endl;

    Token token2 = scanner.getNextToken();
    assert(token2.type() == LexemType::id);
    assert(token2.str() == "main");
    cout << " Идентификатор 'main': "; token2.print(cout); cout << endl;

    Token token3 = scanner.getNextToken();
    assert(token3.type() == LexemType::kwreturn);
    cout << " Ключевое слово 'return': "; token3.print(cout); cout << endl;

    Token token4 = scanner.getNextToken();
    assert(token4.type() == LexemType::id);
    assert(token4.str() == "x");
    cout << " Идентификатор 'x': "; token4.print(cout); cout << endl;

    Token token5 = scanner.getNextToken();
    assert(token5.type() == LexemType::id);
    assert(token5.str() == "my_var123");
    cout << " Идентификатор 'my_var123': "; token5.print(cout); cout << endl;
}

void testPunctuation() {
    cout << " Тест пунктуации " << endl;
    istringstream input("(){}[],;:");
    Scanner scanner(input);

    LexemType expected[] = {
        LexemType::lpar, LexemType::rpar, LexemType::lbrace,
        LexemType::rbrace, LexemType::lbracket, LexemType::rbracket,
        LexemType::comma, LexemType::semicolon, LexemType::colon
    };

    for (int i = 0; i < 9; i++) {
        Token token = scanner.getNextToken();
        assert(token.type() == expected[i]);
        cout << " Пунктуация: "; token.print(cout); cout << endl;
    }
}

void testOperators() {
    cout << " Тест операторов " << endl;
    istringstream input("! != < <= = == + ++ | || & && > * -");
    Scanner scanner(input);

    Token token1 = scanner.getNextToken();
    assert(token1.type() == LexemType::opnot);
    cout << " Оператор '!': "; token1.print(cout); cout << endl;

    Token token2 = scanner.getNextToken();
    assert(token2.type() == LexemType::opne);
    cout << " Оператор '!=': "; token2.print(cout); cout << endl;

    Token token3 = scanner.getNextToken();
    assert(token3.type() == LexemType::oplt);
    cout << " Оператор '<': "; token3.print(cout); cout << endl;

    Token token4 = scanner.getNextToken();
    assert(token4.type() == LexemType::ople);
    cout << " Оператор '<=': "; token4.print(cout); cout << endl;

    Token token5 = scanner.getNextToken();
    assert(token5.type() == LexemType::opassign);
    cout << " Оператор '=': "; token5.print(cout); cout << endl;

    Token token6 = scanner.getNextToken();
    assert(token6.type() == LexemType::opeq);
    cout << " Оператор '==': "; token6.print(cout); cout << endl;

    Token token7 = scanner.getNextToken();
    assert(token7.type() == LexemType::opplus);
    cout << " Оператор '+': "; token7.print(cout); cout << endl;

    Token token8 = scanner.getNextToken();
    assert(token8.type() == LexemType::opinc);
    cout << " Оператор '++': "; token8.print(cout); cout << endl;

    Token token9 = scanner.getNextToken();
    assert(token9.type() == LexemType::error);
    cout << " Ошибка для '|': "; token9.print(cout); cout << endl;

    Token token10 = scanner.getNextToken();
    assert(token10.type() == LexemType::opor);
    cout << " Оператор '||': "; token10.print(cout); cout << endl;

    Token token11 = scanner.getNextToken();
    assert(token11.type() == LexemType::error);
    cout << " Ошибка для '&': "; token11.print(cout); cout << endl;

    Token token12 = scanner.getNextToken();
    assert(token12.type() == LexemType::opand);
    cout << " Оператор '&&': "; token12.print(cout); cout << endl;

    Token token13 = scanner.getNextToken();
    assert(token13.type() == LexemType::opgt);
    cout << " Оператор '>': "; token13.print(cout); cout << endl;

    Token token14 = scanner.getNextToken();
    assert(token14.type() == LexemType::opmult);
    cout << " Оператор '*': "; token14.print(cout); cout << endl;

    Token token15 = scanner.getNextToken();
    assert(token15.type() == LexemType::opminus);
    cout << " Оператор '-': "; token15.print(cout); cout << endl;

    Token token16 = scanner.getNextToken();
    assert(token16.type() == LexemType::eof);
    cout << " Конец потока после операторов" << endl;
}

void testCharAndString() {
    cout << " Тест символьных и строковых констант " << endl;
    istringstream input("'a' \"hello\" 'X' \"test string\"");
    Scanner scanner(input);

    Token token1 = scanner.getNextToken();
    assert(token1.type() == LexemType::chr);
    assert(token1.value() == 'a');
    cout << " Символ 'a': "; token1.print(cout); cout << endl;

    Token token2 = scanner.getNextToken();
    assert(token2.type() == LexemType::str);
    assert(token2.str() == "hello");
    cout << " Строка \"hello\": "; token2.print(cout); cout << endl;

    Token token3 = scanner.getNextToken();
    assert(token3.type() == LexemType::chr);
    assert(token3.value() == 'X');
    cout << " Символ 'X': "; token3.print(cout); cout << endl;

    Token token4 = scanner.getNextToken();
    assert(token4.type() == LexemType::str);
    assert(token4.str() == "test string");
    cout << " Строка \"test string\": "; token4.print(cout); cout << endl;
}

void testErrors() {
    cout << " Тест обработки ошибок " << endl;

    istringstream input1("''");
    Scanner scanner1(input1);
    Token token1 = scanner1.getNextToken();
    assert(token1.type() == LexemType::error);
    cout << "Пустая символьная константа: "; token1.print(cout); cout << endl;

    // Тест |
    istringstream input2("|");
    Scanner scanner2(input2);
    Token token2 = scanner2.getNextToken();
    assert(token2.type() == LexemType::error);
    cout << " Одиночный '|': "; token2.print(cout); cout << endl;

    // Тест &
    istringstream input3("&");
    Scanner scanner3(input3);
    Token token3 = scanner3.getNextToken();
    assert(token3.type() == LexemType::error);
    cout << " Одиночный '&': "; token3.print(cout); cout << endl;

    // Тест неподдерживаемого символа
    istringstream input4("#");
    Scanner scanner4(input4);
    Token token4 = scanner4.getNextToken();
    assert(token4.type() == LexemType::error);
    cout << " Неподдерживаемый символ '#': "; token4.print(cout); cout << endl;

    // Тест символа с несколькими символами в константе
    istringstream input5("'ab'");
    Scanner scanner5(input5);
    Token token5 = scanner5.getNextToken();
    assert(token5.type() == LexemType::error);
    cout << " Многозначная символьная константа: "; token5.print(cout); cout << endl;
}

void testComplexCode() {
    cout << "Тест комплексного кода" << endl;
    istringstream input("int main() {\n    return 0;\n}");
    Scanner scanner(input);

    Token token1 = scanner.getNextToken();
    assert(token1.type() == LexemType::kwint);

    Token token2 = scanner.getNextToken();
    assert(token2.type() == LexemType::id);
    assert(token2.str() == "main");

    Token token3 = scanner.getNextToken();
    assert(token3.type() == LexemType::lpar);

    Token token4 = scanner.getNextToken();
    assert(token4.type() == LexemType::rpar);

    Token token5 = scanner.getNextToken();
    assert(token5.type() == LexemType::lbrace);

    Token token6 = scanner.getNextToken();
    assert(token6.type() == LexemType::kwreturn);

    Token token7 = scanner.getNextToken();
    assert(token7.type() == LexemType::num);
    assert(token7.value() == 0);

    Token token8 = scanner.getNextToken();
    assert(token8.type() == LexemType::semicolon);

    Token token9 = scanner.getNextToken();
    assert(token9.type() == LexemType::rbrace);

    Token token10 = scanner.getNextToken();
    assert(token10.type() == LexemType::eof);

    cout << " тут все окей" << endl;
}

int main() {
    cout << " Тесты SCANNERа" << endl;

    try {
        testEmptyInput();
        testNumbers();
        testIdentifiersAndKeywords();
        testPunctuation();
        testOperators();
        testCharAndString();
        testErrors();
        testComplexCode();

        cout << "\n Ура " << endl;
        cout << " Конечный автомат сделан" << endl;
        cout << " Лексический анализатор готов " << endl;

    } catch (const exception& e) {
        cout << " ОШИБКА В ТЕСТАХ!!!!!!!!!: " << e.what() << endl;
        return 1;
    }

    return 0;
}
