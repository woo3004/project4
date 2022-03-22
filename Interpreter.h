#pragma once


#include "Datalog.h"
#include "Database.h"

using namespace std;

class Interpreter {

private:
    Datalog datalog;
    vector<Predicate> schemeVec;
    vector<Predicate> factVec;
    vector<Rule> ruleVec;
    vector<Predicate> queryVec; 
    Database database;

public:
    Interpreter();

    Interpreter(Datalog data) {
        datalog = data;
        schemeVec = data.getSchemeSet();
        factVec = data.getFactSet();
        ruleVec = data.getRuleSet();
        for(unsigned i = 0; i < ruleVec.size(); i++) {
            ruleVec.at(i).removeHead();
        }
        queryVec = data.getQuerySet();
        
        for(int i = 0; i < (int)schemeVec.size(); ++i){
            string schemeName = schemeVec.at(i).getID();
            vector<Parameter> schemeParams = schemeVec.at(i).getParameter();
            Scheme scheme;
            for(int j = 0; j < (int)schemeParams.size(); ++j){
                string value = schemeParams.at(j).getParaVal();
                scheme.push_back(value);
            }
            Relation newRelation(schemeName, scheme);
            database.insert(pair<string, Relation>(schemeName, newRelation));
        }
        
        for(int i = 0; i < (int)factVec.size(); ++i){
            string factName = factVec.at(i).getID();
            vector<Parameter> factParams = factVec.at(i).getParameter();
            Tuple tuple;
            for(int j = 0; j < (int)factParams.size(); ++j){
                string value = factParams.at(j).getParaVal();
                tuple.push_back(value);
            }
            (database.at(factName)).addTuple(tuple);
        }
    };



    Relation evalPred(Predicate myPredicate) {
        string predicateName = myPredicate.getID();
        Relation myRelation = database.at(predicateName);
        vector<Parameter> predParams = myPredicate.getParameter();
        vector<int> positions;
        vector<string> variableNames;
        map<string, int> variables;
        for(int i = 0; i < (int)predParams.size(); i++) {
            if((predParams.at(i).getParaVal().at(0) == '\'')) {
                myRelation = myRelation.select(predParams.at(i).getParaVal(), i, myRelation);
            }
            else {
                map<string, int> :: iterator duplicate = variables.find(predParams.at(i).getParaVal());
                if(duplicate == variables.end()) {
                    positions.push_back(i);
                    variableNames.push_back(predParams.at(i).getParaVal());
                    variables.insert(pair<string, int>(predParams.at(i).getParaVal(), i));
                }
                else {
                    myRelation = myRelation.select(duplicate->second, i, myRelation);
                }
            }
            
        }
        myRelation = myRelation.project(positions, myRelation);
        myRelation = myRelation.rename(variableNames, myRelation);
        
        return myRelation;
    }

    void evalRule(Rule myRule) {

        vector<Predicate> rulePreds = myRule.getRuleSet();
        vector<Relation> relVec;
        for(auto rp : rulePreds) {
            Relation newRelation = evalPred(rp);
            relVec.push_back(newRelation);
        }
        int relVecSize = (int)relVec.size();
        for(int i = 0; i < relVecSize; i++) {
            if(i == relVecSize - 1) {
                break;
            }
            else {
                relVec.at(i+1) = relVec.at(i).join(relVec.at(i), relVec.at(i+1));
            }
        }
        Relation newRelation = relVec.at(relVecSize-1);
        
        Predicate headPredicate = myRule.getHeadpred();
        vector<Parameter> headPredParams = headPredicate.getParameter();
        int headPredSize = (int)headPredParams.size();
        int relParamSize = (int)newRelation.getScheme().size();
        vector<int> locate;
        vector<string> renameVals;

        for(int i = 0; i < headPredSize; i++){
            for(int j = 0; j < relParamSize; j++) {
                if(headPredParams.at(i).getParaVal() == newRelation.getScheme().at(j)){
                    locate.push_back(j); 
                }
            }
        }
        Relation tempRel = database.at(headPredicate.getID());
        for(int i = 0; i < (int)tempRel.getScheme().size(); i++){
            renameVals.push_back(tempRel.getScheme().at(i));
        }
        
        newRelation = newRelation.project(locate, newRelation);
        newRelation = newRelation.rename(renameVals, newRelation);
        database.at(headPredicate.getID()).combine(newRelation);
    }

    void evalRules() {
        int num = 0;
        int be = 0;
        int af = 0;
        
        cout << "Rule Evaluation" << endl;
        do{
            be = database.getSize();
            for(int i = 0; i < (int)ruleVec.size(); i++){
                cout << ruleVec.at(i).newRuleString();
                evalRule(ruleVec.at(i));
                cout << endl;
            }
            af = database.getSize();
            num++;
        } while(be != af);

        cout << endl << "Schemes populated after " << num << " passes through the Rules." << endl << endl;
    }

    void evalQueries() {
        cout << "Query Evaluation" << endl;
        for(int i = 0; i < (int)queryVec.size(); ++i) {
            Relation newRelation = evalPred(queryVec.at(i));
            cout << queryVec.at(i).getID() << "(" << queryVec.at(i).parameterString() << ")? ";
            if(newRelation.getSet().empty()) {
                cout << "No";
            }
            else {
                cout << newRelation.toString();
            }
            if(i != (int)queryVec.size()-1) {
                cout << endl;
            }
        }
        cout << endl;
    }
    
};

