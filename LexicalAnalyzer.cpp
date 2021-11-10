#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"
#include "Token.cpp"

TokenCodes LexicalAnalyzer::getLexemeGroup(string lexeme){
  if(regex_match(lexeme, regex("(\\+)"))){
    return PLUS;
  }
  else if(regex_match(lexeme, regex("(\\-)"))){
    return MINUS;
  }
  else if(regex_match(lexeme, regex("(\\*)"))){
    return TIMES;
  }
  else if(regex_match(lexeme, regex("(\\=)"))){
    return EQL;
  }
  else if(regex_match(lexeme, regex("(\\()"))){
    return LPAREN;
  }
  else if(regex_match(lexeme, regex("(\\))"))){
    return RPAREN;
  }
  else if(regex_match(lexeme, regex("(\\,)"))){
    return COMMA;
  }
  else if(regex_match(lexeme, regex("(\\;)"))){
    return SEMICOLON;
  }
  else if(regex_match(lexeme, regex("(\\/)"))){
    return SLASH;
  }
  else if(regex_match(lexeme, regex("(\\/=)"))){
    return NEQ;
  }
  else if(regex_match(lexeme, regex("(\\:)"))){
    return COLON;
  }
  else if(regex_match(lexeme, regex("(\\:=)"))){
    return BECOMES;
  }
  else if(regex_match(lexeme, regex("(\\<)"))){
    return LSS;
  }
  else if(regex_match(lexeme, regex("(\\<=)"))){
    return LEQ;
  }
  else if(regex_match(lexeme, regex("(\\>)"))){
    return GTR;
  }
  else if(regex_match(lexeme, regex("(\\>=)"))){
    return GEQ;
  }
  else if(regex_match(lexeme, regex("(begin)"))){
    return BEGINSYM;
  }
  else if(regex_match(lexeme, regex("(boolean)"))){
    return BOOLSYM;
  }
  else if(regex_match(lexeme, regex("(else)"))){
    return ELSESYM;
  }
  else if(regex_match(lexeme, regex("(end)"))){
    return ENDSYM;
  }
  else if(regex_match(lexeme, regex("(false)"))){
    return FALSESYM;
  }
  else if(regex_match(lexeme, regex("(get)"))){
    return GETSYM;
  }
  else if(regex_match(lexeme, regex("(if)"))){
    return IFSYM;
  }
  else if(regex_match(lexeme, regex("(is)"))){
    return ISSYM;
  }
  else if(regex_match(lexeme, regex("(integer)"))){
    return INTSYM;
  }
  else if(regex_match(lexeme, regex("(loop)"))){
    return LOOPSYM;
  }
  else if(regex_match(lexeme, regex("(newline)"))){
    return NEWLINE;
  }
  else if(regex_match(lexeme, regex("(not)"))){
    return NOTSYM;
  }
  else if(regex_match(lexeme, regex("(null)"))){
    return NULLSYM;
  }
  else if(regex_match(lexeme, regex("(procedure)"))){
    return PROCSYM;
  }
  else if(regex_match(lexeme, regex("(put)"))){
    return PUTSYM;
  }
  else if(regex_match(lexeme, regex("(rem)"))){
    return REMSYM;
  }
  else if(regex_match(lexeme, regex("(then)"))){
    return THENSYM;
  }
  else if(regex_match(lexeme, regex("(true)"))){
    return TRUESYM;
  }
  else if(regex_match(lexeme, regex("(while)"))){
    return WHILESYM;
  }
  else if(regex_match(lexeme, regex("([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])*"))){
    return IDENT;
  }
  else if(regex_match(lexeme, regex("([0-9])*"))){
    return NUMLIT;
  }
  else{
    return NAL;
  }
}

void LexicalAnalyzer::getNextLineFromFile(){
  input = "";

  char temp;

  while(true){
    temp = sourceCodeFile->get();
    if(temp == '\n'){
      input += '\n';
      break; 
    }
    if(sourceCodeFile->eof()){
      input += '\0';
      break;
    } 

    input += temp;
  }

  inputSize = input.size();
  max = max + inputSize;
}


LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
  sourceCodeFile = scf;

  input = "";
  inputSize = 0;
  inputPtr = 0;
  endOfInputFlag = false;
  newLineFlag = true;
  max = 0;
}

int LexicalAnalyzer::getCurrentCharPositionNumber()
{
  return (max-inputSize)+(inputPtr);
}

Token* LexicalAnalyzer::getNextToken()
{
  Token *t;

  string tempLexemeName = "";
  TokenCodes tempLexemeGroup;
   
  if(endOfInputFlag){
      return new Token(EOI, "End Of Input", ((max-inputSize)+(inputPtr-tempLexemeName.size())));
  }
  if(newLineFlag){
    getNextLineFromFile();
    newLineFlag = false;
  }

  for(inputPtr; inputPtr <= inputSize; inputPtr++){
    if(input[inputPtr] == ' ' ){
      tempLexemeGroup = getLexemeGroup(tempLexemeName);
      if(tempLexemeGroup == IDENT && tempLexemeName.size() > 10){
        string x;
        for(int i = 0; i < 10; i++){
          x += tempLexemeName[i];
        }
        tempLexemeName = x;
      }
      if(tempLexemeGroup == NUMLIT && tempLexemeName.size() > 10){
        string x;
        for(int i = 0; i < 10; i++){
          x += tempLexemeName[i];
        }
        tempLexemeName = x;
      }
      t = new Token(tempLexemeGroup,tempLexemeName,((max-inputSize)+(inputPtr-tempLexemeName.size())));
      inputPtr++;
      break;
    } else if(input[inputPtr]  == '\n'){
      newLineFlag = true;
      tempLexemeGroup = getLexemeGroup(tempLexemeName);
      if(tempLexemeGroup == IDENT && tempLexemeName.size() > 10){
        string x;
        for(int i = 0; i < 10; i++){
          x += tempLexemeName[i];
        }
        tempLexemeName = x;
      }
      if(tempLexemeGroup == NUMLIT && tempLexemeName.size() > 10){
        string x;
        for(int i = 0; i < 10; i++){
          x += tempLexemeName[i];
        }
        tempLexemeName = x;
      }
      t = new Token(tempLexemeGroup,tempLexemeName,((max-inputSize)+(inputPtr-tempLexemeName.size())));
      inputPtr = 0;
      break;
    } else if(input[inputPtr] == '\0'){
      endOfInputFlag = true;
      tempLexemeGroup = getLexemeGroup(tempLexemeName);
      if(tempLexemeGroup == IDENT && tempLexemeName.size() > 10){
        string x;
        for(int i = 0; i < 10; i++){
          x += tempLexemeName[i];
        }
        tempLexemeName = x;
      }
      if(tempLexemeGroup == NUMLIT && tempLexemeName.size() > 10){
        string x;
        for(int i = 0; i < 10; i++){
          x += tempLexemeName[i];
        }
        tempLexemeName = x;
      }
      t = new Token(tempLexemeGroup,tempLexemeName,((max-inputSize)+(inputPtr-tempLexemeName.size())));
      break;
    } else{
      tempLexemeName += input[inputPtr];
    }
  }
  
  return t;
}

