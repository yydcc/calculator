#include <iostream>
#include "Scanner.h"
#include <string>
#include "Token.h"
#include "Parser.h"
using namespace std;
int main()
{
    string str;
    while (getline(cin, str) && str != "$quit")
    {

        Scanner myScanner(str);
        vector<Token> TokenList = myScanner.run();
        for (auto it = TokenList.begin(); it != TokenList.end(); it++)
        {
            cout << it->getTokenDiscription() << "\n";
        }
        Parser myParser(TokenList);
        myParser.run();
        cout << myParser.getInfo() << endl;
        myParser.showAST();
        cout << endl;
    }
}