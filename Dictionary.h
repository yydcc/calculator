#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <map>
#include "token.h"
using namespace std;
class Dictionary
{
public:
    Dictionary();
    bool haveToken(const string &name) const;
    Token getToken(const string &name);

private:
    void addToken(string name, Token newToken);

private:
    map<string, Token> dictionary_;
};

#endif