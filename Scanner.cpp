#include "Scanner.h"
#include <cassert>
#include <iostream>
using namespace std;
Scanner::Scanner(const string &inputLine) : line(inputLine), currentPosition(0)
{
}
char Scanner::peekNextchar()
{
    if (currentPosition == line.size() - 1)
        return EOF;
    else
        return line[currentPosition + 1];
}
char Scanner::getCurrentchar()
{
    if (currentPosition == line.size())
        return EOF;
    else
        return line[currentPosition];
}
void Scanner::moveBack()
{
    currentPosition--;
}
void Scanner::moveForward()
{
    currentPosition++;
}
vector<Token> &Scanner::run()
{

    Token newToken(TokenType::UNKNOWN);
    do
    {
        newToken = getNextToken();

        if (newToken.getTokenType() == TokenType::UNKNOWN)
        {
            break;
        }
        tokenList.push_back(newToken);
        moveForward();
    } while (newToken.getTokenType() != TokenType::UNKNOWN);
    return tokenList;
}
Token Scanner::handleNumber(string &buffer)
{
    char nextChar = peekNextchar();
    TokenType state = TokenType::INTEGER;
    while (nextChar != EOF)
    {
        if (isdigit(nextChar))
        {
            buffer += nextChar;
            moveForward();
            nextChar = peekNextchar();
        }
        else if (nextChar == '.')
        {
            buffer += nextChar;
            moveForward();
            state = TokenType::UNKNOWN;
            break; // 退出进行判断能否匹配小数
        }
        else
        {
            state = TokenType::INTEGER; // 整数匹配完成
            break;
        }
    }

    nextChar = peekNextchar();
    while (nextChar != EOF)
    {
        if (isdigit(nextChar))
        {
            state = TokenType::DECIMAL;
            buffer += nextChar;
            moveForward();
            nextChar = peekNextchar();
        }
        else
        {
            break;
        }
    }
    if (state == TokenType::INTEGER)
    {
        return Token(state, buffer, stoi(buffer), 0);
    }
    else if (state == TokenType::DECIMAL)
    {
        return Token(state, buffer, stod(buffer), 0);
    }
    else
    {
        return Token(TokenType::UNKNOWN);
    }
}
Token Scanner::handleIdentifer(string &buffer) // 匹配标识符或关键字
{
    char nextChar = peekNextchar();
    TokenType state = TokenType::IDENTIFIER;
    while (nextChar != EOF)
    {
        if (nextChar == '$' || nextChar == '_' || isalnum(nextChar))
        {
            buffer += nextChar;
            moveForward();
            nextChar = peekNextchar();
        }
        else
        {
            break; // 标识符匹配结束
        }
    }
    if (dictionary_.haveToken(buffer)) // 如果该标识符或关键字已经被存储过，参照以往的记录
    {
        auto checkToken = dictionary_.getToken(buffer);
        return checkToken;
    }
    else
    {
        state = TokenType::IDENTIFIER;
        return Token(state, buffer, 0);
    }
}
Token Scanner::getNextToken()
{
    char startChar = getCurrentchar();
    while (startChar == ' ' && peekNextchar() != EOF)
    {
        moveForward();
        startChar = getCurrentchar();
    }
    if (startChar == ' ' && peekNextchar() == EOF)
    {
        state = false;
        return Token(TokenType::UNKNOWN);
    }
    string tokenBuffer;
    tokenBuffer += startChar;
    if (isdigit(startChar))
    {
        return handleNumber(tokenBuffer);
    }
    else if (startChar == '$' || startChar == '_' || isalpha(startChar))
    {
        return handleIdentifer(tokenBuffer);
    }
    else if (startChar == '(')
    {
        auto it = dictionary_.getToken(string(1, startChar));
        return it;
    }
    else if (startChar == ')')
    {
        auto it = dictionary_.getToken(string(1, startChar));
        return it;
    }
    else if (startChar == '+')
    {
        auto it = dictionary_.getToken(string(1, startChar));
        return it;
    }
    else if (startChar == '-')
    {
        auto it = dictionary_.getToken(string(1, startChar));
        return it;
    }
    else if (startChar == '*')
    {
        auto it = dictionary_.getToken(string(1, startChar));
        return it;
    }
    else if (startChar == '/')
    {
        auto it = dictionary_.getToken(string(1, startChar));
        return it;
    }
    else if (startChar == '%')
    {
        auto it = dictionary_.getToken(string(1, startChar));
        return it;
    }
    else if (startChar == '<')
    {
        char nextChar = peekNextchar();
        if (nextChar == '=')
        {
            moveForward();
            auto it = dictionary_.getToken("<=");
            return it;
        }
        else
        {
            auto it = dictionary_.getToken("<");
            return it;
        }
    }
    else if (startChar == '>')
    {
        char nextChar = peekNextchar();
        if (nextChar == '=')
        {
            moveForward();
            auto it = dictionary_.getToken(">=");
            return it;
        }
        else
        {
            auto it = dictionary_.getToken(">");
            return it;
        }
    }
    else if (startChar == '=')
    {
        char nextChar = peekNextchar();
        if (nextChar == '=')
        {
            moveForward();
            auto it = dictionary_.getToken("==");
            return it;
        }
        else
        {
            auto it = dictionary_.getToken("=");
            return it;
        }
    }
    else if (startChar == '!')
    {
        char nextChar = peekNextchar();
        if (nextChar == '=')
        {
            moveForward();
            auto it = dictionary_.getToken("!=");
            return it;
        }
        else
        {
            auto it = dictionary_.getToken("!");
            return it;
        }
    }
    else if (startChar == '&')
    {
        char nextChar = peekNextchar();
        if (nextChar == '&')
        {
            moveForward();
            auto it = dictionary_.getToken("&&");
            return it;
        }
        else
        {
            return Token(TokenType::UNKNOWN);
        }
    }
    else if (startChar == '|')
    {
        char nextChar = peekNextchar();
        if (nextChar == '|')
        {
            moveForward();
            auto it = dictionary_.getToken("||");
            return it;
        }
        else
        {
            return Token(TokenType::UNKNOWN);
        }
    }
    else
    {
        return Token(TokenType::UNKNOWN);
    }
}