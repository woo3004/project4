#pragma once

#include <sstream>
#include "Predicate.h"
#include "Rule.h"
#include <set>

class Datalog {
    private:
        vector<Predicate> scheme_set;
        vector<Predicate> fact_set;
        vector<Predicate> query_set;
        set<string> domain_list;
        vector<Rule> rule_set;
        Rule r;

    public:
        void addScheme(Predicate pre) {
            scheme_set.push_back(pre);
        }


        
        void addFact(Predicate pre) {
            fact_set.push_back(pre);
        }


        void addQuery(Predicate pre) {
            query_set.push_back(pre);
        }

        void addRule(Rule r) {
            rule_set.push_back(r);
        }

        void setRule(Rule rule) {
            r = rule;
        }

        Rule getRule() {
            return r;
        }

        vector<Rule>& getRuleSet() {
            return rule_set;
        }

        vector<Predicate>& getSchemeSet() {
            return scheme_set;
        }

        vector<Predicate>& getFactSet() {
            return fact_set;
        }

        vector<Predicate>& getQuerySet() {
            return query_set;
        }

        void addSet(string val) {
            domain_list.insert(val);
        }

        string schemeString() {
            stringstream ss;
            ss << "Schemes" << "(" << scheme_set.size() << ")" << ":\n";
            for(unsigned i = 0; i < scheme_set.size(); i++) {
                ss << "  " << scheme_set.at(i).getID() << "(" << scheme_set.at(i).parameterString() << ")\n";
            }

            return ss.str();
        }

        string factString() {
            stringstream ss;
            ss << "Facts" << "(" << fact_set.size() << ")" << ":\n";
            for(unsigned i = 0; i < fact_set.size(); i++) {
                ss << "  " << fact_set.at(i).getID() << "(" << fact_set.at(i).parameterString() << ").\n";
            }

            return ss.str();
        }

        string queryString() {
            stringstream ss;
            ss << "Queries" << "(" << query_set.size() << ")" << ":\n";
            for(unsigned i = 0; i < query_set.size(); i++) {
                ss << "  " << query_set.at(i).getID() << "(" << query_set.at(i).parameterString() << ")?\n";
            }

            return ss.str();
        }

        string setString() {
            stringstream ss;
            ss << "Domain" << "(" << domain_list.size() << ")" << ":\n";
            for (set<string>::iterator it=domain_list.begin(); it!=domain_list.end(); it++) {
                ss << "  " << *it << "\n";
            }

            return ss.str();
        }

};