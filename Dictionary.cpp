#include "dictionary.h"

Dictionary::Dictionary()
{
    // 操作符
    addToken("(", Token(TokenType::LEFT_PAREN, "(", 0));
    addToken(")", Token(TokenType::RIGHT_PAREN, ")", 0));
    addToken("+", Token(TokenType::PLUS, "+", 0));
    addToken("-", Token(TokenType::MINUS, "-", 0));
    addToken("*", Token(TokenType::MULTIPLY, "*", 0));
    addToken("/", Token(TokenType::DIVIDE, "/", 0));
    addToken("%", Token(TokenType::MOD, "%", 0));
    addToken("=", Token(TokenType::ASSIGN, "=", 0));
    addToken("==", Token(TokenType::EQUAL, "==", 0));
    addToken("!=", Token(TokenType::NOT_EQUAL, "!=", 0));
    addToken(">=", Token(TokenType::GREATER_OR_EQUAL, ">=", 0));
    addToken(">", Token(TokenType::GREATER_THAN, ">", 0));
    addToken("<=", Token(TokenType::LESS_OR_EQUAL, "<=", 0));
    addToken("<", Token(TokenType::LESS_THAN, "<", 0));
    addToken("!", Token(TokenType::LOGICAL_NOT, "!", 0));
    addToken("&&", Token(TokenType::LOGICAL_AND, "&&", 0));
    addToken("||", Token(TokenType::LOGICAL_OR, "||", 0));

    // 关键字
    addToken("$help", Token(TokenType::HELP, "$help", 0));
    addToken("$quit", Token(TokenType::QUIT, "$quit", 0));
    addToken("id", Token(TokenType::IDENTIFIER, "id", 0));
    addToken("integer", Token(TokenType::INTEGER, "integer", 0));
    addToken("decimal", Token(TokenType::DECIMAL, "decimal", 0));
    addToken("decimal", Token(TokenType::BOOLEAN, "bool", 0));
    // 标识符
    addToken("true", Token(TokenType::BOOLEAN, "true", true, 0));
    addToken("false", Token(TokenType::BOOLEAN, "false", false, 0));
}

void Dictionary::addToken(string name, Token newToken)
{
    dictionary_.insert(make_pair(name, newToken));
}

Token Dictionary::getToken(const ::string &name)
{
    auto iter = dictionary_.find(name);
    if (iter != dictionary_.end())
    {
        return iter->second;
    }
    else
    {
        return Token(TokenType::UNKNOWN);
    }
}

bool Dictionary::haveToken(const ::string &name) const
{
    auto iter = dictionary_.find(name);

    if (iter != dictionary_.end())
    {
        return true;
    }

    return false;
}
