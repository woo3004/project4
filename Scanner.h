#pragma once
#include <cctype>
#include <fstream>
#include "Token.h"
class Scanner
{
private:
    string input;
    unsigned int lineNum = 1;
    unsigned int badStringLine = 0;
    unsigned int tokenNum = 0;

public:
    Scanner(const string &input) : input(input)
    {}
    
    int GetSize() {
        return this-> input.size();
    }
    
    int GetTokenNum() {
        return this-> tokenNum;
    }

    string ReadFile(string fileName) {
        ifstream file(fileName);
        stringstream ss;
        ss << file.rdbuf();

        return ss.str();
    }


    Token scanToken()
    {
        string value = "";
        TokenType type = TBD;
        lineNum = lineNum + badStringLine;
        badStringLine = 0;
        unsigned int size = 0;
        
        if (input.size()==0) {
            type = END_FILE;
            size = 0;
        }

        
        while (input.size() > 0 && isspace(input.at(0)))
        {   
            if(input.size()==1){
                if (input.at(0) == '\n') {
                    lineNum++;
                }
                input.clear();
                type = END_FILE;
            }
            else {
                if (input.at(0) == '\n') {
                    lineNum++;
                }
                input = input.substr(1);
            }
        }


        if (input.size() > 0) {
            switch (input.at(0))
            {
                case ',':
                    size = 1;
                    type = COMMA;
                    break;
                case '.':
                    size = 1;
                    type = PERIOD;
                    break;
                case '?':
                    size = 1; 
                    type = Q_MARK;
                    break;
                case '(':
                    size = 1;
                    type = LEFT_PAREN;
                    break;
                case ')':
                    size = 1;
                    type = RIGHT_PAREN;
                    break;
                case ':':
                    if(input.size()>1){
                        if(input.at(1) == '-'){
                            size = 2;
                            type = COLON_DASH;
                            break;
                        }
                    }
                    size = 1;
                    type = COLON;
                    break;
                case '*':
                    size = 1;
                    type = MULTIPLY;
                    break;
                case '+':
                    size = 1; 
                    type = ADD;
                    break;
                case '!':
                    type = UNDEFINED;
                    size = 1;
                    break;
                case '@':
                    type = UNDEFINED;
                    size = 1;
                    break;
                case '$':
                    type = UNDEFINED;
                    size = 1;
                    break;
                case '%':
                    type = UNDEFINED;
                    size = 1;
                    break;
                case '^':
                    type = UNDEFINED;
                    size = 1;
                    break;
                case '&':
                    type = UNDEFINED;
                    size = 1;
                case '-':
                    type = UNDEFINED;
                    size = 1;
                
            }
        }

        
        if(type == TBD) {
            if (input.substr(0,7) == "Queries" && !isalpha(input.at(7)))
            {   
                type = QUERIES;
                size = 7;
            }
            else if (input.substr(0,5) == "Rules" && !isalpha(input.at(5)))
            {
                type = RULES;
                size = 5;
            }
            else if (input.substr(0,5) == "Facts" && !isalpha(input.at(5)))
            {   
                type = FACTS;
                size = 5;
            }
            else if (input.substr(0,7) == "Schemes" && !isalpha(input.at(7)))
            {
                type = SCHEMES;
                size = 7;
            }

            else if (input.at(0)=='\'') {
                type = STRING;
                size = 0;
                while(size != input.size() && input.at(size+1)!='\'') {
                    if(input.at(size+1)=='\n') {
                        badStringLine++;
                    }
                    if(input.substr(size+1).size()==1 && input.at(size+1)!='\'') {
                        type = UNDEFINED;
                        break;
                    }
                    size++;
                }
                size = size+2;                
            }

            else if (input.at(0) == '#') {
                type = COMMENT;
                size = 0;
                while(size != input.size() && input.at(size)!='\n') {
                    size++;
                }
            }


            else {
        
                    if(!isalpha(input.at(0))) {
                        type = UNDEFINED;
                        size = 1;
                    }
                    else{
                        type = ID;
                        size = 0;
                        while(size != input.size() ) {
                            if(!(isalpha(input.at(size))) && !(int(char((input.at(size)))) > 47 && int(char(input.at(size))) < 58)) {

                                break;
                            }
                            size++;
                        }
                    }
            }
        }



        value = input.substr(0, size);
        this->input = input.substr(size, input.size()-size);
        tokenNum++;

        return Token(type, value, lineNum);
    }
};

