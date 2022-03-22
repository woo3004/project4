#pragma once

#include "Scanner.h"
#include "Datalog.h"
#include <vector>
#include <iostream>


class Parser {
    private:
    vector<Token> tokens;
    Predicate pred;
    Parameter para;
    Datalog date;
    Rule r;
    Token errToken;
    bool err = true;


    public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }

    void setError() {
        err = false;
    }

    void removeComment() {
        for(unsigned i = 0; i < tokens.size(); i++) {
            if(tokens.at(i).getType() == COMMENT) {
                tokens.erase(tokens.begin()+i);
                i--;
            }
            
        }
    }

    TokenType tokenType() const {
        return tokens.at(0).getType();
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
    }
    void throwError() {
        setError();
        errToken.setToken(tokens.at(0).getType(), tokens.at(0).getValue(), tokens.at(0).getLineNum());
        tokens.erase(tokens.begin()+1,tokens.end());
    }

    void match(TokenType t) {
        if(err) {
            if (tokenType() == t)
                advanceToken();
            else
                throwError();
        }
    }

    void idList() {
        if(err) {
            if (tokenType() == COMMA) {
                match(COMMA);
                para.setParameter(tokens.at(0).getValue());
                pred.addParameter(para);
                match(ID);
                idList();
            } else {
                // lambda
            }
        }
    }

    void stringList() {
        if(err) {
            if (tokenType() == COMMA) {
                match(COMMA);
                para.setParameter(tokens.at(0).getValue());
                date.addSet(tokens.at(0).getValue());
                pred.addParameter(para);
                match(STRING);
                stringList();
            }
            else {
                // lambda
            }
        }
    }

    void schemeList() {
        if(err) {
            if (tokenType() == ID) {
                scheme();
                schemeList();
            }
            else {
                // lambda
            }
        }
    }

    void factList() {
        if(err) {
            if (tokenType() == ID) {
                fact();
                factList();
            }
            else {
                // lambda
            }
        }
    }


    void ruleList() {
        if(err){
            if (tokenType() == ID) {
                rule();
                ruleList();
            }
            else {
                // lambda
            }
        }
    }

    void queryList() {
        if (tokenType() == ID) {
            query();
            queryList();
        }
        else {
            // lambda
        }
    }

    void predicateList() {
        if(err) {
            if (tokenType() == COMMA) {
                match(COMMA);
                predicate();
                //
                pred.getParameter().clear();
                predicateList();
            }
            else {
                // lambda
            }
        }
    }

    void parameterList() {
        if(err){
            if (tokenType() == COMMA) {
                match(COMMA);
                parameter();
                parameterList();
            }
            else {
                // lambda
            }
        }
    }

    


    void scheme() {
        if (tokenType() == ID) {
            pred.setId(tokens.at(0).getValue());
            match(ID);
            match(LEFT_PAREN);
            para.setParameter(tokens.at(0).getValue());
            pred.addParameter(para);
            match(ID);
            idList();
            match(RIGHT_PAREN);
            date.addScheme(pred);
            pred.getParameter().clear();
        } else {
            throwError();
        }
    }

    void fact() {
        if (tokenType() == ID) {
            pred.setId(tokens.at(0).getValue());
            match(ID);
            match(LEFT_PAREN);
            para.setParameter(tokens.at(0).getValue());
            date.addSet(tokens.at(0).getValue());
            pred.addParameter(para);
            match(STRING);
            stringList();
            match(RIGHT_PAREN);
            match(PERIOD);
            date.addFact(pred);
            pred.getParameter().clear();
        } else {
            throwError();
        }
    }

    void rule() {
        if (tokenType() == ID) {
            headPredicate();
            match(COLON_DASH);
            predicate();
            pred.getParameter().clear();
            predicateList();
            match(PERIOD);
            r.addRuleVec(r);
            date.addRule(r);
            pred.getParameter().clear();
            r.getRuleSet().clear();
        } else {
            throwError();
        }
    }

    void headPredicate() {
        pred.setId(tokens.at(0).getValue());
        match(ID);
        match(LEFT_PAREN);
        para.setParameter(tokens.at(0).getValue());
        pred.addParameter(para);
        match(ID);
        idList();
        match(RIGHT_PAREN);
        r.addRule(pred);
        pred.getParameter().clear();
    }

    void predicate() {
        pred.setId(tokens.at(0).getValue());
        match(ID);
        match(LEFT_PAREN);
        parameter();
        parameterList();
        match(RIGHT_PAREN);
        //
        r.addRule(pred);
        
    }

    void parameter() {
        if(tokenType() == ID) {
            para.setParameter(tokens.at(0).getValue());
            pred.addParameter(para);
            match(ID);
        }
        if(tokenType() == STRING) {
            para.setParameter(tokens.at(0).getValue());
            pred.addParameter(para);
            match(STRING);
        }
    }

    void query() {
        if (tokenType() == ID) {
            predicate();
            match(Q_MARK);
            date.addQuery(pred);
            pred.getParameter().clear();
        } else {
            throwError();
        }
    }

    void datalogProgram() {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();

        if (err) {
            match(FACTS);
            match(COLON);
            factList();
        }

        if (err) {
            match(RULES);
            match(COLON);
            ruleList();
        }

        if (err) {            
            match(QUERIES);
            match(COLON);
            query();
            queryList();
            match(END_FILE);
        }


        // if(tokens.size()==0 && err) {
        //     cout << "Success!" << endl;
        //     cout << date.schemeString();
        //     cout << date.factString();
        //     cout << r.ruleString();
        //     cout << date.queryString();
        //     cout << date.setString();
        // }

        // else {
        //     cout << "Failure!" << endl;
        //     cout << "  " << errToken.toString() << endl;
        // }
        date.setRule(r);

    }

    Datalog getDataLog() {
        return date;
    }
    
};

