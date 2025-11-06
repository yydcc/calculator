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

#ifndef __TOKEN__
#define __TOKEN__
#include <string>
using namespace std;
enum class TokenType
{
    INTEGER,
    DECIMAL,
    BOOLEAN,
    IDENTIFIER,
    OPERATOR,
    DELIMITER,
    END_OF_LINE,
    KEYWORD,
    // symbols
    LEFT_PAREN,  // (
    RIGHT_PAREN, // )
    PLUS,        // +
    MINUS,       // -
    MULTIPLY,    // *
    DIVIDE,      // /
    ASSIGN,      // =
    MOD,         // %
    // ralation symbols
    LESS_OR_EQUAL,    // <=
    LESS_THAN,        // <
    GREATER_OR_EQUAL, // >=
    GREATER_THAN,     // >
    EQUAL,            // ==
    NOT_EQUAL,        // !=
    LOGICAL_NOT,      // !
    LOGICAL_AND,      // &&
    LOGICAL_OR,       // ||
    ORDER,
    HELP, //$help
    QUIT, //$quit
    UNKNOWN
};
// enum class TokenValue
// {
// 针对变量的值做类型划分
//
//   orders
// HELP, //$help
// QUIT, //$quit
//
// UNRESERVED
//
// };
class Token
{
public:
    Token(TokenType type = TokenType::UNKNOWN);
    Token(TokenType type, string identiferName, int priority);
    Token(TokenType type, string identiferName, int intValue, int priority);
    Token(TokenType type, string identiferName, double decimalValue, int priority);
    Token(TokenType type, string identiferName, bool booleanValue, int priority);
    string getTokenDiscription();
    TokenType getTokenType() const;
    int getIntValue() const;
    double getDecimalValue() const;
    bool getBooleanType() const;
    string getIndentiferName() const;

private:
    TokenType type; // 大的类型
    string ID;      // 每个类型的名字，字面值
    int priority;   // 对于操作符设定的优先级
    // 标识符的值或常量的值
    int intValue = 0;
    double decimalValue = 0.0;
    bool booleanValue = false;
};

#endif
#ifndef __PARSER__
#define __PARSER__
#include "Token.h"
#include <vector>
#include <stdexcept>
using namespace std;
enum class ASTNodeType
{
    STATEMENT,
    ASSIGNMENT,
    EXPREESION,
    AND_EXPRESSION,
    EQUAL_EXPRESSION,
    RELATION_EXPRESSION,
    ADD_EXPRESSION,
    MUL_EXPRESSION,
    UNARY_EXPRESSION,
    PRIMARY,
    BASIC_TOKEN,

};
struct ASTNode
{
    ASTNodeType nodeType;
    Token myToken;
    ASTNode *firstChild;
    ASTNode *nextSibling;
    ASTNode();
    ASTNode(const ASTNodeType type, const Token &token_);
    ~ASTNode();
    string getInfo() const;
    string to_string() const;
    void showMyTree(int depth);
};

class Parser
{
public:
    Parser(const vector<Token> &tokenList);
    void run();
    string getInfo() const;
    void showAST() const;

private:
    ASTNode *ASTroot;
    vector<Token> tokenList;
    int currentPosition;
    Token currentToken;
    string info;
    Token getCurrentToken();
    Token peekNextToken();
    void error(const std::string &msg);
    void advance();
    void consume(TokenType type);
    ASTNode *statTail();
    ASTNode *Exp();
    ASTNode *ExpTail();
    ASTNode *AndExp();
    ASTNode *AndExpTail();
    ASTNode *EqExp();
    ASTNode *EqExpTail();
    ASTNode *RelExp();
    ASTNode *RelExpTail();
    ASTNode *AddExp();
    ASTNode *AddExpTail();
    ASTNode *MulExp();
    ASTNode *MulExpTail();
    ASTNode *UnaryExp();
    ASTNode *Primary();
};

#endif
#include "Parser.h"
#include <iostream>
#include <stack>
using namespace std;
string ASTNode::to_string() const
{
    string s;
    switch (nodeType)
    {
    case ASTNodeType::STATEMENT:
        s = "STATEMENT";
        break;
    case ASTNodeType::ASSIGNMENT:
        s = "ASSIGNMENT";
        break;
    case ASTNodeType::EXPREESION:
        s = "EXPRESSION";
        break;
    case ASTNodeType::AND_EXPRESSION:
        s = "AND_EXPRESSION";
        break;
    case ASTNodeType::EQUAL_EXPRESSION:
        s = "EQUAL_EXPRESSION";
        break;
    case ASTNodeType::RELATION_EXPRESSION:
        s = "RELATION_EXPRESSION";
        break;
    case ASTNodeType::ADD_EXPRESSION:
        s = "ADD_EXPRESSION";
        break;
    case ASTNodeType::MUL_EXPRESSION:
        s = "MUL_EXPRESSION";
        break;
    case ASTNodeType::UNARY_EXPRESSION:
        s = "UNARY_EXPRESSION";
        break;
    case ASTNodeType::PRIMARY:
        s = "PRIMARY";
        break;
    case ASTNodeType::BASIC_TOKEN:
        s = "BASIC_TOKEN";
        break;
    default:
        s = "UNKNOWN";
    }
    return s;
}

ASTNode::ASTNode()
{
}
ASTNode::ASTNode(const ASTNodeType type, const Token &token_ = Token(TokenType::UNKNOWN)) : nodeType(type), myToken(token_), firstChild(nullptr), nextSibling(nullptr)
{
}
ASTNode::~ASTNode()
{
    ASTNode *cur = firstChild;
    if (cur != nullptr)
    {
        cur->~ASTNode();
    }
    delete cur;
    cur = nextSibling;
    if (cur != nullptr)
    {
        cur->~ASTNode();
    }
    delete cur;
}
string ASTNode::getInfo() const
{
    if (nodeType == ASTNodeType::BASIC_TOKEN)
    {
        return myToken.getIndentiferName();
    }
    else
    {
        return to_string();
    }
}
void ASTNode::showMyTree(int depth)
{

    stack<pair<ASTNode *, int>> nodeStack;
    nodeStack.push({this, 0}); // 从根节点开始
    while (!nodeStack.empty())
    {
        auto [node, depth] = nodeStack.top();
        nodeStack.pop();
        for (int i = 0; i < depth; ++i)
        {
            cout << "  ";
        }
        cout << node->getInfo() << endl;
        if (node->nextSibling)
        {
            nodeStack.push({node->nextSibling, depth});
        }
        if (node->firstChild)
        {
            nodeStack.push({node->firstChild, depth + 1});
        }
    }
}
Parser::Parser(const vector<Token> &tokenList) : tokenList(tokenList), currentPosition(0)
{

    currentToken = getCurrentToken();
}

void Parser::advance()
{
    currentPosition++;
    currentToken = getCurrentToken();
}
Token Parser::getCurrentToken()
{
    if (currentPosition == tokenList.size())
    {
        return Token();
    }
    else
    {
        return tokenList[currentPosition];
    }
}
Token Parser::peekNextToken()
{
    if (currentPosition == tokenList.size() - 1)
    {
        return Token();
    }
    else
    {
        return tokenList[currentPosition + 1];
    }
}
void Parser::error(const std::string &msg)
{
    throw std::runtime_error("Parser Error: " + msg);
}
string Parser::getInfo() const
{
    return info;
}
void Parser::showAST() const
{
    ASTroot->showMyTree(0);
}

void Parser::consume(TokenType type)
{
    if (currentToken.getTokenType() == type)
    {
        advance();
    }
    else
    {
        error("Expected " +
              std::to_string(static_cast<int>(type)) + " but got " + std::to_string(static_cast<int>(currentToken.getTokenType())));
    }
}
void Parser::run()
{
    ASTroot = new ASTNode(ASTNodeType::STATEMENT);
    Token nextToken = peekNextToken();
    // 尽管文法能够识别只有id和以id开始的各种表达式，如Stat_prime -> ASSIGN Exp| MulExpTail AddExpTail RelExpTail EqExpTail AndExpTail ExpTail
    // ，但在处理id(+|-|*|/|%| or |&&|<)exp的过程中调用过程过多，且与常规表达式的调用起点不一致，故我选择进行超前搜索一位，简化处理
    if (currentToken.getTokenType() == TokenType::IDENTIFIER && nextToken.getTokenType() == TokenType::ASSIGN) // 更改为只处理赋值表达式
    {
        ASTNode *fc = new ASTNode(ASTNodeType::ASSIGNMENT);
        ASTroot->firstChild = fc;
        fc->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, Token(TokenType::IDENTIFIER, "id", 0));
        fc->firstChild->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::IDENTIFIER);
        fc->firstChild->nextSibling = statTail();
    }
    else if (currentToken.getTokenType() == TokenType::ORDER)
    {
        info = "this is an order";
        ASTroot->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::ORDER);
    }
    else
    {
        info = "this is an expression";
        ASTroot->firstChild = Exp();
    }
}
ASTNode *Parser::statTail()
{
    ASTNode *curp = nullptr;
    if (currentToken.getTokenType() == TokenType::ASSIGN)
    {
        curp = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::ASSIGN);
        info = "this is an assignment expression";
        curp->nextSibling = Exp();
    }
    // else
    // { // id打头的非赋值表达式

    // ASTNode *fc = nullptr;
    // TokenType mytype = currentToken.getTokenType();
    // switch (mytype)
    // {
    // case TokenType::MULTIPLY:
    // curp = new ASTNode(ASTNodeType::MUL_EXPRESSION);
    // fc = MulExpTail();
    // break;
    // case TokenType::PLUS:
    // case TokenType::MINUS:
    // curp = new ASTNode(ASTNodeType::ADD_EXPRESSION);
    // fc = AddExpTail();
    // break;
    // case TokenType::GREATER_THAN:
    // case TokenType::LESS_THAN:
    // case TokenType::GREATER_OR_EQUAL:
    // case TokenType::LESS_OR_EQUAL:
    // curp = new ASTNode(ASTNodeType::RELATION_EXPRESSION);
    // fc = RelExpTail();
    // break;
    // case TokenType::EQUAL:
    // case TokenType::NOT_EQUAL:
    // curp = new ASTNode(ASTNodeType::EQUAL_EXPRESSION);
    // fc = EqExpTail();
    // break;
    // case TokenType::LOGICAL_AND:
    // curp = new ASTNode(ASTNodeType::AND_EXPRESSION);
    // fc = AndExpTail();
    // break;
    // case TokenType::LOGICAL_OR:
    // curp = new ASTNode(ASTNodeType::EXPREESION);
    // fc = ExpTail();
    // break;
    // default:;
    // }

    // curp->firstChild = fc;
    // }
    return curp;
}
ASTNode *Parser::Exp()
{
    ASTNode *curp = nullptr;
    ASTNode *fc = AndExp();
    ASTNode *sc = ExpTail();
    if (fc != nullptr)
    {
        curp = new ASTNode(ASTNodeType::EXPREESION);
        curp->firstChild = fc;
        curp->firstChild->nextSibling = sc;
    }
    return curp;
}
ASTNode *Parser::ExpTail()
{
    ASTNode *curp = nullptr;
    if (currentToken.getTokenType() == TokenType::LOGICAL_OR)
    {
        curp = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::LOGICAL_OR);
        curp->nextSibling = AndExp();
        if (curp->nextSibling != nullptr)
            curp->nextSibling->nextSibling = ExpTail();
    }
    return curp;
}

ASTNode *Parser::AndExp()
{
    ASTNode *curp = nullptr;
    ASTNode *fc = EqExp();
    ASTNode *sc = AndExpTail();
    if (fc != nullptr)
    {
        fc->nextSibling = sc;
        curp = new ASTNode(ASTNodeType::AND_EXPRESSION);
        curp->firstChild = fc;
    }
    return curp;
}

ASTNode *Parser::AndExpTail()
{
    ASTNode *curp = nullptr;
    if (currentToken.getTokenType() == TokenType::LOGICAL_AND)
    {
        curp = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::LOGICAL_AND);
        curp->nextSibling = EqExp();
        if (curp->nextSibling != nullptr)
            curp->nextSibling->nextSibling = AndExpTail();
    }
    return curp;
}
ASTNode *Parser::EqExp()
{
    ASTNode *curp = nullptr;
    ASTNode *fc = RelExp();
    ASTNode *sc = EqExpTail();
    if (fc != nullptr)
    {
        fc->nextSibling = sc;
        curp = new ASTNode(ASTNodeType::EQUAL_EXPRESSION);
        curp->firstChild = fc;
    }
    return curp;
}
ASTNode *Parser::EqExpTail()
{
    ASTNode *curp = nullptr;
    if (currentToken.getTokenType() == TokenType::EQUAL || currentToken.getTokenType() == TokenType::NOT_EQUAL)
    {
        curp = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(currentToken.getTokenType());
        curp->nextSibling = RelExp();
        if (curp->nextSibling != nullptr)
            curp->nextSibling->nextSibling = EqExpTail();
    }
    return curp;
}
ASTNode *Parser::RelExp()
{
    ASTNode *curp = nullptr;
    ASTNode *fc = AddExp();
    ASTNode *sc = RelExpTail();
    if (fc != nullptr)
    {
        fc->nextSibling = sc;
        curp = new ASTNode(ASTNodeType::RELATION_EXPRESSION);
        curp->firstChild = fc;
    }
    return curp;
}

ASTNode *Parser::RelExpTail()
{

    ASTNode *curp = nullptr;
    if (currentToken.getTokenType() == TokenType::GREATER_THAN || currentToken.getTokenType() == TokenType::LESS_THAN ||
        currentToken.getTokenType() == TokenType::GREATER_OR_EQUAL || currentToken.getTokenType() == TokenType::LESS_OR_EQUAL)
    {
        curp = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(currentToken.getTokenType());
        curp->nextSibling = AddExp();
        if (curp->nextSibling != nullptr)
            curp->nextSibling->nextSibling = RelExpTail();
    }
    return curp;
}
ASTNode *Parser::AddExp()
{

    ASTNode *curp = nullptr;
    ASTNode *fc = MulExp();
    ASTNode *sc = AddExpTail();
    if (fc != nullptr)
    {
        fc->nextSibling = sc;
        curp = new ASTNode(ASTNodeType::ADD_EXPRESSION);
        curp->firstChild = fc;
    }
    return curp;
}
ASTNode *Parser::AddExpTail()
{
    ASTNode *curp = nullptr;
    if (currentToken.getTokenType() == TokenType::PLUS || currentToken.getTokenType() == TokenType::MINUS)
    {
        curp = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(currentToken.getTokenType());
        curp->nextSibling = MulExp();
        if (curp->nextSibling != nullptr)
            curp->nextSibling->nextSibling = AddExpTail();
    }
    return curp;
}

ASTNode *Parser::MulExp()
{

    ASTNode *curp = nullptr;
    ASTNode *fc = UnaryExp();
    ASTNode *sc = MulExpTail();
    if (fc != nullptr)
    {
        fc->nextSibling = sc;
        curp = new ASTNode(ASTNodeType::MUL_EXPRESSION);
        curp->firstChild = fc;
    }
    return curp;
}

ASTNode *Parser::MulExpTail()
{
    ASTNode *curp = nullptr;
    if (currentToken.getTokenType() == TokenType::MULTIPLY ||
        currentToken.getTokenType() == TokenType::DIVIDE ||
        currentToken.getTokenType() == TokenType::MOD)
    {
        curp = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(currentToken.getTokenType());
        curp->nextSibling = UnaryExp();
        if (curp->nextSibling != nullptr)
            curp->nextSibling->nextSibling = MulExpTail();
    }
    return curp;
}

ASTNode *Parser::UnaryExp()
{
    ASTNode *curp = nullptr;
    if (currentToken.getTokenType() == TokenType::PLUS ||
        currentToken.getTokenType() == TokenType::MINUS ||
        currentToken.getTokenType() == TokenType::LOGICAL_NOT)
    {
        ASTNode *fc = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(currentToken.getTokenType());
        ASTNode *sc = UnaryExp();
        if (sc != nullptr)
        {
            curp = new ASTNode(ASTNodeType::UNARY_EXPRESSION);
            curp->firstChild = fc;
            fc->nextSibling = sc;
        }
        else
            delete fc;
    }
    else
    {
        ASTNode *fc = Primary();
        if (fc != nullptr)
        {
            curp = new ASTNode(ASTNodeType::UNARY_EXPRESSION);
            curp->firstChild = fc;
        }
    }
    return curp;
}

ASTNode *Parser::Primary()
{
    ASTNode *curp = new ASTNode(ASTNodeType::PRIMARY);

    if (currentToken.getTokenType() == TokenType::LEFT_PAREN)
    {
        ASTNode *fc = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::LEFT_PAREN);
        ASTNode *sc = Exp();
        ASTNode *tc = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::RIGHT_PAREN);

        if (sc != nullptr)
        {
            curp->firstChild = fc;
            fc->nextSibling = sc;
            sc->nextSibling = tc;
        }
        else
        {
            delete tc;
            delete sc;
            delete fc;
            delete curp;
            curp = nullptr;
        }
    }
    else if (currentToken.getTokenType() == TokenType::IDENTIFIER)
    {
        curp->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, Token(TokenType::IDENTIFIER, "id", 0));
        curp->firstChild->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::IDENTIFIER);
    }
    else if (currentToken.getTokenType() == TokenType::INTEGER)
    {
        curp->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, Token(TokenType::INTEGER, "integer", 0));
        curp->firstChild->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::INTEGER);
    }
    else if (currentToken.getTokenType() == TokenType::DECIMAL)
    {
        curp->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, Token(TokenType::DECIMAL, "decimal", 0));
        curp->firstChild->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::DECIMAL);
    }
    else if (currentToken.getTokenType() == TokenType::BOOLEAN)
    {
        curp->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, Token(TokenType::BOOLEAN, "bool", 0));
        curp->firstChild->firstChild = new ASTNode(ASTNodeType::BASIC_TOKEN, currentToken);
        consume(TokenType::BOOLEAN);
    }
    else
    {
        error("Unexpected token in Primary");
    }

    return curp;
}