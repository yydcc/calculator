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