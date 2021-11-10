#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>
#include <string>

#include "Token.h"
#include "TokenCodes.h"

class LexicalAnalyzer
{
  private:
    ifstream *sourceCodeFile;
    string input;
    int inputSize;
    int inputPtr;
    int max;
    bool endOfInputFlag;
    bool newLineFlag;
    void getNextLineFromFile();
    void getNextLexeme();
    TokenCodes getLexemeGroup(string lexeme);


  public:
    LexicalAnalyzer(ifstream*);
    int getCurrentCharPositionNumber();
    Token* getNextToken();
};

#endif
