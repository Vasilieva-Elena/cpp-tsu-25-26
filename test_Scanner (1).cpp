#include "Scaner.h"
#include <sstream>
#include <cassert>
#include <iostream>

using namespace std;

void test_empty_stream() {
    cout << "Тест пустого потока - ";
    istringstream iss("");
    Scanner scanner(iss);
    Token token = scanner.getNextToken();
    assert(token.type() == LexemType::eof);
    cout << "OK" << endl;
}

void test_numbers() {
    cout << "Тест чисел - ";
    istringstream iss("123 45");
    Scanner scanner(iss);
    
    Token token1 = scanner.getNextToken();
    assert(token1.type() == LexemType::num);
    assert(token1.value() == 123);
    
    Token token2 = scanner.getNextToken();
    assert(token2.type() == LexemType::num);
    assert(token2.value() == 45);
    
    cout << "OK" << endl;
}

void test_identifiers_and_keywords() {
    cout << "Тест идентификаторов и ключевых слов - ";
    istringstream iss("variable if while return");
    Scanner scanner(iss);
    
    Token token1 = scanner.getNextToken();
    assert(token1.type() == LexemType::id);
    assert(token1.str() == "variable");
    
    Token token2 = scanner.getNextToken();
    assert(token2.type() == LexemType::kwif);
    
    Token token3 = scanner.getNextToken();
    assert(token3.type() == LexemType::kwwhile);
    
    Token token4 = scanner.getNextToken();
    assert(token4.type() == LexemType::kwreturn);
    
    cout << "OK" << endl;
}

void test_operators() {
    cout << "Тест операторов - ";
    istringstream iss("! != < <= = == + ++ | || & && * - >");
    Scanner scanner(iss);
    
    assert(scanner.getNextToken().type() == LexemType::opnot);
    assert(scanner.getNextToken().type() == LexemType::opne);
    assert(scanner.getNextToken().type() == LexemType::oplt);
    assert(scanner.getNextToken().type() == LexemType::ople);
    assert(scanner.getNextToken().type() == LexemType::opassign);
    assert(scanner.getNextToken().type() == LexemType::opeq);
    assert(scanner.getNextToken().type() == LexemType::opplus);
    assert(scanner.getNextToken().type() == LexemType::opinc);
    
    // Проверка ошибок для одиночных | и &
    Token token = scanner.getNextToken();
    assert(token.type() == LexemType::error);
    
    token = scanner.getNextToken();
    assert(token.type() == LexemType::opor);
    
    token = scanner.getNextToken();
    assert(token.type() == LexemType::error);
    
    token = scanner.getNextToken();
    assert(token.type() == LexemType::opand);
    
    assert(scanner.getNextToken().type() == LexemType::opmult);
    assert(scanner.getNextToken().type() == LexemType::opminus);
    assert(scanner.getNextToken().type() == LexemType::opgt);
    
    cout << "OK" << endl;
}

void test_punctuation() {
    cout << "Тест знаков пунктуации - ";
    istringstream iss("(){}[];,:");
    Scanner scanner(iss);
    
    assert(scanner.getNextToken().type() == LexemType::lpar);
    assert(scanner.getNextToken().type() == LexemType::rpar);
    assert(scanner.getNextToken().type() == LexemType::lbrace);
    assert(scanner.getNextToken().type() == LexemType::rbrace);
    assert(scanner.getNextToken().type() == LexemType::lbracket);
    assert(scanner.getNextToken().type() == LexemType::rbracket);
    assert(scanner.getNextToken().type() == LexemType::semicolon);
    assert(scanner.getNextToken().type() == LexemType::comma);
    assert(scanner.getNextToken().type() == LexemType::colon);
    
    cout << "OK" << endl;
}

void test_strings_and_chars() {
    cout << "Тест строк и символов - ";
    istringstream iss("\"hello\" 'a'");
    Scanner scanner(iss);
    
    Token token1 = scanner.getNextToken();
    assert(token1.type() == LexemType::str);
    assert(token1.str() == "hello");
    
    Token token2 = scanner.getNextToken();
    assert(token2.type() == LexemType::chr);
    assert(token2.value() == 'a');
    
    cout << "OK" << endl;
}

void test_errors() {
    cout << "Тест ошибок - ";
    
    // Тест пустого символа
    istringstream iss1("''");
    Scanner scanner1(iss1);
    Token token1 = scanner1.getNextToken();
    assert(token1.type() == LexemType::error);
    
    // Тест слишком длинного символа
    istringstream iss2("'ab'");
    Scanner scanner2(iss2);
    Token token2 = scanner2.getNextToken();
    assert(token2.type() == LexemType::error);
    
    // Тест незакрытой строки
    istringstream iss3("\"unclosed");
    Scanner scanner3(iss3);
    Token token3 = scanner3.getNextToken();
    assert(token3.type() == LexemType::error);
    
    // Тест неподдерживаемого символа
    istringstream iss4("@");
    Scanner scanner4(iss4);
    Token token4 = scanner4.getNextToken();
    assert(token4.type() == LexemType::error);
    
    cout << "OK" << endl;
}

void test_whitespace() {
    cout << "Тест пробельных символов - ";
    istringstream iss("  \t\n  token");
    Scanner scanner(iss);
    
    Token token = scanner.getNextToken();
    assert(token.type() == LexemType::id);
    assert(token.str() == "token");
    
    cout << "OK" << endl;
}

int main() {
    cout << "Тесты для ScanneR." << endl << endl;
    
    test_empty_stream();
    test_numbers();
    test_identifiers_and_keywords();
    test_operators();
    test_punctuation();
    test_strings_and_chars();
    test_errors();
    test_whitespace();
    
    cout << endl << "Все тесты проходят))" << endl;
    return 0;
}

