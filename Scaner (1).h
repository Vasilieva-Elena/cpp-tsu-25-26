#ifndef SCANER_H
#define SCANER_H

#include <string>
#include <ostream>
#include <map>
#include <istream>

using namespace std;

enum class LexemType {
    num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket,
    semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc,
    opeq, opne, oplt, opgt, ople, opnot, opor, opand, kwint, kwchar,
    kwif, kwelse, kwswitch, kwcase, kwwhile, kwfor, kwreturn, kwin,
    kwout, eof, error
};

class Token {
private:
    LexemType _type;
    int _value;
    string _str;

public:
    Token(LexemType type);
    Token(int value);
    Token(LexemType type, const string &str);
    Token(char c);
    void print(ostream &stream);
    LexemType type();
    int value();
    string str();
};

class Scanner {
private:
    istream &_stream;
    static const map<char, LexemType> punctuation;
    static const map<string, LexemType> keywords;
public:
    Scanner(istream &stream) : _stream(stream) {}
    Token getNextToken();
};

#endif
