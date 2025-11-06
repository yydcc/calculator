#include "Token.h"
#include <cassert>
Token::Token(TokenType type)
    : type(type)
{
}

Token::Token(TokenType type, string identiferName, int priority)
    : type(type), ID(identiferName), priority(priority)
{
}
Token::Token(TokenType type, string identiferName, int intValue, int priority = 0)
    : type(type), ID(identiferName), intValue(intValue), priority(priority)
{
}
Token::Token(TokenType type, string identiferName, double decimalValue, int priority = 0)
    : type(type), ID(identiferName), decimalValue(decimalValue), priority(priority)
{
}
Token::Token(TokenType type, string identiferName, bool booleanValue, int priority = 0)
    : type(type), ID(identiferName), booleanValue(booleanValue), priority(priority)
{
}

TokenType Token::getTokenType() const
{
    return type;
}

int Token::getIntValue() const
{
    return intValue;
}
double Token::getDecimalValue() const
{
    return decimalValue;
}
bool Token::getBooleanType() const
{
    return booleanValue;
}
string Token::getIndentiferName() const
{
    return ID;
}
string Token::getTokenDiscription()
{
    string discription;
    if (type == TokenType::BOOLEAN)
    {
        discription += "Type:bool\tValue:" + ID;
    }
    else if (type == TokenType::DECIMAL)
    {
        discription += "Type:decimal\tid:" + ID + "\tValue:" + to_string(decimalValue);
    }
    else if (type == TokenType::INTEGER)
    {
        discription += "Type:integer\tid:" + ID + "\tValue:" + to_string(intValue);
    }
    else if (type == TokenType::IDENTIFIER)
    {
        discription += "Type:identifer\tid:" + ID + "\tKind:";
    }
    else if (type == TokenType::KEYWORD)
    {
        discription += "Type:keyword\tid:" + ID;
    }
    else if (type >= TokenType::LEFT_PAREN && type <= TokenType::LOGICAL_OR)
    {
        discription += "Type:operator\tid:" + ID;
    }
    else
    {
        discription += "Type:Error\tValue:Error";
    }
    return discription;
}