#include "Scaner.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream ifile("example.minic");
    Scanner scanner(ifile);
    for (;;) {
        Token currentLexem = scanner.getNextToken();
        currentLexem.print(cout);
        cout << endl;
        if (currentLexem.type() == LexemType::error || currentLexem.type() == LexemType::eof) {
            break;
        }
    }
    ifile.close(); 
}
