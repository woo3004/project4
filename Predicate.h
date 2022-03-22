#pragma once

#include <vector>
#include <string>
#include "Parameter.h"
#include <iostream>
#include <sstream>

using namespace std;
//SNAP(S, N, A, P)
class Predicate {
    private:
        string id; // ex) snap
        vector<Parameter> parameter_set;

    public:
        

        void setId(string id) {
            this -> id = id;
        }

        void addParameter(Parameter para) {
            parameter_set.push_back(para);
        }

        string getID() {
            return id;
        }

        vector<Parameter>& getParameter() {
            return parameter_set;
        }

        string parameterString() {
            stringstream ss;
            for(unsigned i = 0; i < parameter_set.size(); i++) {
                ss << parameter_set.at(i).getParaVal();
                if(i != parameter_set.size() - 1) {
                    ss << ",";
                }
            }

            return ss.str();
        }
        


};