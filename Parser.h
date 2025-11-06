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