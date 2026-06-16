#include "Scaner.h"
#include <ostream>
#include <cctype>
#include <map>

using namespace std;


const map<char, LexemType> Scanner::punctuation = {
    {'(', LexemType::lpar}, {')', LexemType::rpar},
    {'{', LexemType::lbrace}, {'}', LexemType::rbrace},
    {'[', LexemType::lbracket}, {']', LexemType::rbracket},
    {';', LexemType::semicolon}, {',', LexemType::comma},
    {':', LexemType::colon}
};

const map<string, LexemType> Scanner::keywords = {
    {"int", LexemType::kwint}, {"char", LexemType::kwchar},
    {"if", LexemType::kwif}, {"else", LexemType::kwelse},
    {"switch", LexemType::kwswitch}, {"case", LexemType::kwcase},
    {"while", LexemType::kwwhile}, {"for", LexemType::kwfor},
    {"return", LexemType::kwreturn}, {"in", LexemType::kwin},
    {"out", LexemType::kwout}
};


Token::Token(LexemType type) : _type(type), _value(0) {}

Token::Token(int value) : _type(LexemType::num), _value(value) {}

Token::Token(LexemType type, const string &str) : _type(type), _str(str) {}

Token::Token(char c) : _type(LexemType::chr), _value(static_cast<int>(c)) {}

void Token::print(ostream &stream) {
    stream << "[";
    switch (_type) {
        case LexemType::num:    stream << "num, " << _value; break;
        case LexemType::chr:    stream << "chr, '" << static_cast<char>(_value) << "'"; break;
        case LexemType::str:    stream << "str, \"" << _str << "\""; break;
        case LexemType::id:     stream << "id, \"" << _str << "\""; break;
        case LexemType::error:  stream << "error, \"" << _str << "\""; break;
        case LexemType::lpar:   stream << "lpar"; break;
        case LexemType::rpar:   stream << "rpar"; break;
        case LexemType::lbrace: stream << "lbrace"; break;
        case LexemType::rbrace: stream << "rbrace"; break;
        case LexemType::lbracket: stream << "lbracket"; break;
        case LexemType::rbracket: stream << "rbracket"; break;
        case LexemType::semicolon: stream << "semicolon"; break;
        case LexemType::comma:  stream << "comma"; break;
        case LexemType::colon:  stream << "colon"; break;
        case LexemType::opassign: stream << "opassign"; break;
        case LexemType::opplus: stream << "opplus"; break;
        case LexemType::opminus: stream << "opminus"; break;
        case LexemType::opmult: stream << "opmult"; break;
        case LexemType::opinc:  stream << "opinc"; break;
        case LexemType::opeq:   stream << "opeq"; break;
        case LexemType::opne:   stream << "opne"; break;
        case LexemType::oplt:   stream << "oplt"; break;
        case LexemType::opgt:   stream << "opgt"; break;
        case LexemType::ople:   stream << "ople"; break;
        case LexemType::opnot:  stream << "opnot"; break;
        case LexemType::opor:   stream << "opor"; break;
        case LexemType::opand:  stream << "opand"; break;
        case LexemType::kwint:  stream << "kwint"; break;
        case LexemType::kwchar: stream << "kwchar"; break;
        case LexemType::kwif:   stream << "kwif"; break;
        case LexemType::kwelse: stream << "kwelse"; break;
        case LexemType::kwswitch: stream << "kwswitch"; break;
        case LexemType::kwcase: stream << "kwcase"; break;
        case LexemType::kwwhile: stream << "kwwhile"; break;
        case LexemType::kwfor:  stream << "kwfor"; break;
        case LexemType::kwreturn: stream << "kwreturn"; break;
        case LexemType::kwin:   stream << "kwin"; break;
        case LexemType::kwout:  stream << "kwout"; break;
        case LexemType::eof:    stream << "eof"; break;
        default:                stream << "???"; break;
    }
    stream << "]";
}

LexemType Token::type() { return _type; }
int Token::value() { return _value; }
string Token::str() { return _str; }

// метод Scanner
Token Scanner::getNextToken() {
    enum class State {
        S0, S1, S2, S3, S4, S5, S7, S8, S9, S10, S11, S12
    };

    State state = State::S0;
    string lexeme;
    int value = 0;
    char c;

    while (true) {
        if (state != State::S0 || _stream.peek() != EOF) {
            c = _stream.get();
        }

        switch (state) {
            case State::S0:
                if (_stream.eof()) {
                    return Token(LexemType::eof);
                }
                else if (isspace(c)) {
                    continue;
                }
                else if (isdigit(c)) {
                    // [0] → [1] при [Digit, value=Digit]
                    value = c - '0';
                    state = State::S1;
                }
                else if (c == '\'') {
                    // [0] → [2] при [ ', value=""]
                    lexeme = "";
                    state = State::S2;
                }
                else if (isalpha(c) || c == '_') {
                    // [0] → [5] при [Letter, value=Letter]
                    lexeme = c;
                    state = State::S5;
                }
                else if (c == '"') {
                    // [0] → [4] при [ ", value=""]
                    lexeme = "";
                    state = State::S4;
                }
                else if (c == '!') {
                    // [0] → [7] при [!]
                    state = State::S7;
                }
                else if (c == '<') {
                    // [0] → [8] при [<]
                    state = State::S8;
                }
                else if (c == '=') {
                    // [0] → [9] при [=]
                    state = State::S9;
                }
                else if (c == '+') {
                    // [0] → [10] при [+]
                    state = State::S10;
                }
                else if (c == '|') {
                    // [0] → [11] при [|]
                    state = State::S11;
                }
                else if (c == '&') {
                    // [0] → [12] при [&]
                    state = State::S12;
                }
                else if (punctuation.count(c)) {
                    // [0] → [0] при [Punct, ret(Punct)]
                    return Token(punctuation.at(c));
                }
                else if (c == '*') {
                    // [0] → [0] при [*, ret(opmult)]
                    return Token(LexemType::opmult);
                }
                else if (c == '-') {
                    // [0] → [0] при [-, ret(opminus)]
                    return Token(LexemType::opminus);
                }
                else if (c == '>') {
                    // [0] → [0] при [>, ret(opgt)]
                    return Token(LexemType::opgt);
                }
                else {
                    // [0] → [--->] при [other] - ошибка
                    return Token(LexemType::error,
                        string("Неподдерживаемый символ: '") + c + "'");
                }
                break;
            // Состояние 1: Число
            case State::S1:
                if (isdigit(c)) {
                    // [1] → [1] при [Digit, value=value*10+Digit]
                    value = value * 10 + (c - '0');
                } else {
                    // [1] → [0] при [other, ret(num, value), <-]
                    _stream.unget();
                    return Token(value);
                }
                break;
            // Состояние 2: Начало символьной константы
            case State::S2:
                if (c == '\'') {
                    // [2] → [--->] при ['] - пустая символьная константа
                    return Token(LexemType::error, "Пустая символьная константа");
                }
                else if (_stream.eof()) {
                    // [2] → [--->] при [$] - конец потока
                    return Token(LexemType::error, "Незакрытая символьная константа");
                }
                else {
                    // [2] → [3] при [other, value=other]
                    lexeme = c;
                    state = State::S3;
                }
                break;
            // Состояние 3: Символьная константа (один символ прочитан)
            case State::S3:
                if (c == '\'') {
                    // [3] → [0] при [', ret(chr, value)]
                    return Token(lexeme[0]);
                }
                else {
                    // [3] → [--->] при [other] - слишком много символов
                    return Token(LexemType::error,
                        "Символьная константа содержит более одного символа");
                }
                break;
            // Состояние 4: Строковая константа
            case State::S4:
                if (c == '"') {
                    // [4] → [0] при [", ret(str, value)]
                    return Token(LexemType::str, lexeme);
                }
                else if (_stream.eof()) {
                    // [4] → [--->] при [$] - конец потока
                    return Token(LexemType::error, "Незакрытая строковая константа");
                }
                else {
                    // [4] → [4] при [other, value += other]
                    lexeme += c;
                }
                break;
                   // Состояние 5: Идентификатор или ключевое слово
            case State::S5:
                if (isalnum(c) || c == '_') {
                    // [5] → [5] при [Letter/Digit, value += Letter/Digit]
                    lexeme += c;
                } else {
                    // [5] → [0] при [other, ret(id/keyword), <-]
                    _stream.unget();
                    if (keywords.count(lexeme)) {
                        return Token(keywords.at(lexeme));
                    } else {
                        return Token(LexemType::id, lexeme);
                    }
                }
                break;
            // Состояние 7: Оператор !
            case State::S7:
                if (c == '=') {
                    // [7] → [0] при [=, ret(opne)]
                    return Token(LexemType::opne);
                }
                else {
                    // [7] → [0] при [other, ret(opnot), <-]
                    _stream.unget();
                    return Token(LexemType::opnot);
                }
                break;
                    // Состояние 8: Оператор <
            case State::S8:
                if (c == '=') {
                    // [8] → [0] при [=, ret(ople)]
                    return Token(LexemType::ople);
                }
                else {
                    // [8] → [0] при [other, ret(oplt), <-]
                    _stream.unget();
                    return Token(LexemType::oplt);
                }
                break;
            // Состояние 9: Оператор =
            case State::S9:
                if (c == '=') {
                    // [9] → [0] при [=, ret(opeq)]
                    return Token(LexemType::opeq);
                }
                else {
                    // [9] → [0] при [other, ret(opassign), <-]
                    _stream.unget();
                    return Token(LexemType::opassign);
                }
                break;
            // Состояние 10: Оператор +
            case State::S10:
                if (c == '+') {
                    // [10] → [0] при [+, ret(opinc)]
                    return Token(LexemType::opinc);
                }
                else {
                    // [10] → [0] при [other, ret(opplus), <-]
                    _stream.unget();
                    return Token(LexemType::opplus);
                }
                break;
            // Состояние 11: Оператор |
            case State::S11:
                if (c == '|') {
                    // [11] → [0] при [|, ret(opor)]
                    return Token(LexemType::opor);
                }
                else {
                    // [11] → [--->] при [other] - одиночный символ |
                    return Token(LexemType::error, "Одиночный символ |");
                }
                break;
            // Состояние 12: Оператор &
            case State::S12:
                if (c == '&') {
                    // [12] → [0] при [&, ret(opand)]
                    return Token(LexemType::opand);
                }
                else {
                    // [12] → [--->] при [other] - одиночный символ &
                    return Token(LexemType::error, "Одиночный символ &");
                }
                break;
        }
    }
}
