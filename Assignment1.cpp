#include <fstream>
#include <iostream>
#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"
#include "LexicalAnalyzer.cpp"

int main(int argc, char *argv[])
{
  ifstream sourceCodeFile;
  LexicalAnalyzer *la;
  Token *nextToken;
  TokenCodes tc;

  sourceCodeFile.open(argv[1], ifstream::in);
  if  (sourceCodeFile.is_open())
  {
    la = new LexicalAnalyzer(&sourceCodeFile);
    do
    {
      nextToken = la->getNextToken();
      cout << *nextToken << endl;
      tc = nextToken->getTokenCode();
      delete nextToken;

      //delete later
      cin.get();
    } while (tc != EOI);
    delete la;
  }
  else
    printf("ERROR - cannot open input file \n");

  return 0;
}
