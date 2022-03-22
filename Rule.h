# pragma once
# include "Predicate.h"
#include <set>

class Rule {
    private:
        Predicate headPred;
        vector<Predicate> rule_set;
        vector<Rule> rule_list;
        set<string> check;

    public:

        void addRule(Predicate pre) {
            rule_set.push_back(pre);
        }

        void removeHead() {
            if(rule_set.size() > 0) {
                rule_set.erase(rule_set.begin());
            }
        }

        vector<Predicate>& getRuleSet() {
            return rule_set;
        }

        vector<Rule>& getRule_list() {
            return rule_list;
        }

        void addRuleVec(Rule r) {
            rule_list.push_back(r);
        }

        void setHeadPred(Predicate head) {
            headPred = head;
        }

        Predicate getHeadpred() {
            return headPred;
        }

        string ruleString() {
            stringstream ss;
            ss << "Rules" << "(" << rule_list.size() << ")" << ":\n";
            for(unsigned i = 0; i < rule_list.size(); i++) {
                ss << "  " << rule_list.at(i).rule_set.at(0).getID()  << "(" 
                << rule_list.at(i).rule_set.at(0).parameterString() << ") :- ";
                headPred = rule_list.at(i).rule_set.at(0);
                for (unsigned j = 1; j < rule_list.at(i).rule_set.size(); j++) {
                    ss << rule_list.at(i).rule_set.at(j).getID() << "(" 
                    << rule_list.at(i).rule_set.at(j).parameterString() << ")";
                    if(j != rule_list.at(i).rule_set.size() - 1) {
                    ss << ",";
                    }
                }
                ss << ".\n";
            }


            return ss.str();
        }

        string newRuleString() {
            stringstream ss;
            for(unsigned i = 0; i < rule_list.size(); i++) {
                for(set<string>::iterator itr = check.begin(); itr != check.end(); itr++) {
                    // cout << "compare " << *itr << " and " << ss.str();
                    if(*itr == ss.str()) {
                        // cout <<  "cleared" << endl;
                        ss.str("");
                        // cout << "remain: " << ss.str() << endl;
                    }
                }
                // cout << "ruleSize: " << rule_list.size() << endl;
                ss << rule_list.at(i).rule_set.at(0).getID()  << "(" 
                << rule_list.at(i).rule_set.at(0).parameterString() << ") :- ";
                headPred = rule_list.at(i).rule_set.at(0);
                for (unsigned j = 1; j < rule_list.at(i).rule_set.size(); j++) {
                    ss << rule_list.at(i).rule_set.at(j).getID() << "(" 
                    << rule_list.at(i).rule_set.at(j).parameterString() << ")";
                    if(j != rule_list.at(i).rule_set.size() - 1) {
                    ss << ",";
                    }
                }
                ss << ".";
                
                check.insert(ss.str());

            }

            

            // cout << "flag" << endl;
            

            
            // for(set<string>::iterator itr = check.begin(); itr != check.end(); itr++) {
            //     if(*itr == ss.str()) {
            //         return "";
            //     }
            // }

            check.insert(ss.str());
            // cout << "add: " << ss.str() << endl;

            return ss.str();
        }


        
};