#pragma once

#include <string>
#include <sstream>

using namespace std;

enum TokenType
{
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END_FILE, TBD
};

string typeName(TokenType type)
{
    switch(type) {
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case UNDEFINED:
            return "UNDEFINED";
        case END_FILE:
            return "EOF";
        default:
            return "BAD TYPE";
    }
}

class Token
{
private:
    TokenType type;
    string value;
    unsigned int lineNum;
public:

    Token(){}

    Token(TokenType type, const string &value, unsigned int lineNum) : type(type), value(value), lineNum(lineNum)
    {}


    const string &getValue() const
    {
        return value;
    }

    void setValue(const string &value)
    {
        Token::value = value;
    }

    TokenType getType() const
    {
        return type;
    }

    

    bool checkEnd() {
        if(type == END_FILE) {
            return true;
        }
        return false;
    }

    void setType(TokenType type)
    {
        Token::type = type;
    }

    unsigned int getLineNum() const
    {
        return lineNum;
    }

    void setLineNum(unsigned int lineNum)
    {
        Token::lineNum = lineNum;
    }

    void setToken(TokenType t, string v, int l) {
        type = t;
        value = v;
        lineNum = l;
    }
    
    string toString()
    {
        stringstream outSS;
        outSS << "(" << typeName(type) << ",\"" << value << "\"," << lineNum << ")";
        return outSS.str();
    }


};


