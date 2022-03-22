#pragma once

#include <iostream>

using namespace std;

class Parameter {
    private:
        string value;
        bool is_Const;
    public:
        void setParameter(string value) {
            this -> value = value;
        }

        string getParaVal() {
            return value;
        }
};