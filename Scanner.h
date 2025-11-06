#ifndef __SCANNER__
#define __SCANNER__
#include "Token.h"
#include "Dictionary.h"
#include <vector>
using namespace std;
class Scanner
{
public:
    Scanner(const string &inputLine);
    vector<Token> &run();

private:
    vector<Token> tokenList;
    char peekNextchar();
    char getCurrentchar();
    void moveBack();
    void moveForward();
    Token getNextToken();
    Token handleNumber(string &buffer);
    Token handleIdentifer(string &buffer);
    string line;
    int currentPosition;
    Dictionary dictionary_;
    bool state;
};

#endif