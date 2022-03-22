#pragma once

#include "Relation.h"
#include <map>


using namespace std;

class Database : public map<string, Relation> {

public:
    Database() {}

    int getSize() {
        int size = 0;
        for(map<string, Relation>::iterator it = this->begin(); it != this->end(); ++it) {
            for(Tuple x : it->second.getSet()) {
                size++;
            }
        }
        
        return size;
    }
    
};