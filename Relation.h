#pragma once

#include <sstream>
#include <set>
#include "Tuple.h"
#include <map>

using namespace std;

class Relation {

private:
string name;
Scheme scheme; 
set<Tuple> tuple_set;


public:
    void addTuple(Tuple t) {
        tuple_set.insert(t);
    };


    bool newAddTuple(Tuple t) {
        pair<set<Tuple>::iterator,bool> insert = tuple_set.insert(t);
        bool inserted = insert.second;
        return inserted;
    };
    
    string getName() {
        return name;
    };

    Scheme getScheme() {
        return scheme;
    };

    set<Tuple> getSet() {
        return tuple_set;
    };

    Relation() {};
    
    Relation(string n, Scheme s) {
        name = n;
        scheme = s;
    };
    
    Relation(string n, set<Tuple> s) {
        name = n;
        tuple_set = s;
    };
    
    Relation(string n) {
        name = n;
    };
    

    // string newToString() {
    //     stringstream ss;
    //     for(Tuple x : tuple_set) {
    //         if(x.empty()) {
                
    //         }
    //         else {
    //             ss << endl << "  ";
    //             for(int i = 0; i < (int)x.size(); ++i) {
    //                 ss << scheme.at(i) << "=" << x.at(i);
    //                 if(i == (int)x.size()-1) {
                        
    //                 }
    //                 else {
    //                     ss << ", ";
    //                 }
    //             }
    //         }
            
    //     }
    //     return ss.str();
    // }

    // string newToString() {
    //     stringstream ss;
    //     for(Tuple tuple : tuple_set) {
    //         if(tuple.empty()) {
                
    //         }
    //         else {
    //             ss << endl << "  ";
    //             for(int i = 0; i < (int)tuple.size(); ++i) {
    //                 ss << scheme.at(i) << "=" << tuple.at(i);
    //                 if(i == (int)tuple.size()-1) {
                        
    //                 }
    //                 else {
    //                     ss << ", ";
    //                 }
    //             }
    //         }
            
    //     }
    //     return ss.str();
    // }

    string toString() {
        stringstream ss;
        if(tuple_set.empty()) {
            ss << "No";
        }
        else {
            ss << "Yes(" << tuple_set.size() << ")";
            for(auto& t : tuple_set) {
                if(t.empty()) {
                    
                }
                else {
                    ss << endl << "  ";
                    for(int i = 0; i < (int)t.size(); ++i) {
                        ss << scheme.at(i) << "=" << t.at(i);
                        if(i == (int)t.size()-1) {
                            
                        }
                        else {
                            ss << ", ";
                        }
                    }
                }
                
            }
        }
        return ss.str();
    };



    Relation select(string constant, int index, Relation relation) {
        Relation newRelation(relation.getName(), relation.getScheme());
        for(auto& t : relation.getSet()) {
            if(t.at(index) == constant) {
                newRelation.addTuple(t);
            }
        }
        return newRelation;
    };

    Relation select(int index1, int index2, Relation relation) {
        Relation newRelation(relation.getName(), relation.getScheme());
        for(auto& t : relation.getSet()) {
            if(t.at(index1) == t.at(index2)) {
                newRelation.addTuple(t);
            }
        }
        return newRelation;
    };


    Relation project(vector<int> positions, Relation relation) {
        Relation newRelation(relation.getName());
        for(auto& t : relation.getSet()) {
            Tuple temp;
            for(int j = 0; j < (int)positions.size(); j++){
                temp.push_back(t.at(positions.at(j)));
                // scheme.push_back(relation.scheme.at(j));
            }
            newRelation.addTuple(temp);
        }
        return newRelation;
    };

    void setScheme(Scheme s) {
        scheme = s;
    }


    Relation rename(vector<string> variables, Relation relation) {
        Relation newRelation(relation.getName(), relation.getSet());
        Scheme temp;
        for(int i = 0; i < (int)variables.size(); i++) {
            temp.push_back(variables.at(i));
        }
        newRelation.setScheme(temp);
        return newRelation;
    };

    // static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
	//     	const Tuple& leftTuple, const Tuple& rightTuple) {
    //     bool flag = true;

    //     for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
    //         const string& leftName = leftScheme.at(leftIndex);
    //         const string& leftValue = leftTuple.at(leftIndex);
    //         cout << "left name: " << leftName << " value: " << leftValue << endl;
    //         for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
    //             const string& rightName = rightScheme.at(rightIndex);
    //             const string& rightValue = rightTuple.at(rightIndex);
    //             cout << "right name: " << rightName << " value: " << rightValue << endl;
    //             if(leftIndex != leftScheme.size()-1) {
    //                 for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
    //                     const string& rightName = rightScheme.at(rightIndex);
    //                     const string& rightValue = rightTuple.at(rightIndex);
    //                     if(leftScheme.at(leftIndex+1) == rightName && leftTuple.at(leftIndex+1) != rightValue) {
    //                         flag = false;
    //                     }
    //                 }
    //             }
                
    //         }
    //     }

    //     return flag;
    // }

    Relation join(const Relation& r) {

        const Scheme& leftScheme = scheme;
        const Scheme& rightScheme = r.scheme;

        for (const Tuple& leftTuple : tuple_set) {
            cout << "left tuple: " << leftTuple.toString(leftScheme) << endl;

            for (const Tuple& rightTuple : r.tuple_set) {
                cout << "right tuple: " << rightTuple.toString(rightScheme) << endl;
            }
        }
        

        return Relation();
    }


    Relation join(Relation rel1, Relation rel2) {
        Scheme newScheme = rel1.getScheme();
        map<int, int> matching;
        for(int i = 0; i < (int)(rel2.getScheme()).size(); ++i){
            bool match = false;
            for(int j = 0; j < (int)(rel1.getScheme()).size(); ++j) {
                if(rel2.getScheme().at(i) == rel1.getScheme().at(j)){
                    matching.insert(pair<int, int>(j, i));
                    match = true;
                }
            }
            if(match == false) {
                newScheme.push_back(rel2.getScheme().at(i));
            }
        }
        
        return joinable(name, newScheme, rel1, rel2, matching);
    }

    Relation joinable(string joinString, Scheme joinScheme, Relation joinRel1, Relation joinRel2, map<int,int> joinMap) {
        Relation joinedRelation(name, joinScheme);
        bool isJoinable = false;
        bool noMatches = false;
        for(Tuple tuple1 : joinRel1.getSet()){
            for(Tuple tuple2 : joinRel2.getSet()){
                if(joinMap.empty()) {
                    isJoinable = true;
                    noMatches = true;
                }
                else {
                    for(map<int, int>::iterator itr = joinMap.begin(); itr!=joinMap.end(); itr++){
                        if(tuple1.at(itr->first) == tuple2.at(itr->second)) {
                            isJoinable = true;
                        }
                        else{
                            isJoinable = false;
                            break;
                        }
                    }
                }
                
                if(isJoinable == true) {
                    Tuple newTuple = tuple1;
                    if(noMatches == true) {
                        for(int i = 0; i < (int)tuple2.size(); i++){
                            newTuple.push_back(tuple2.at(i));
                        }
                    }
                    else {
                        for(int i = 0; i < (int)tuple2.size(); i++){
                            bool unique = true;
                            for(map<int, int>::iterator itr = joinMap.begin(); itr!=joinMap.end(); itr++){
                                if(itr->second == i) {
                                    unique = false;
                                }
                            }
                            if(unique == true) {
                                newTuple.push_back(tuple2.at(i));
                            }
                        }
                    }
                    joinedRelation.newAddTuple(newTuple);
                }
            }
        }

        return joinedRelation;
    }


    void combine(Relation rel){
        for(auto tuple : rel.getSet()) {
            if(this->newAddTuple(tuple) == false) {
            }
            else {
                cout << endl  << "  ";
                for(int i = 0; i < (int)this->scheme.size(); i++) {
                    cout << this->scheme.at(i) << "=" << tuple.at(i);
                    if(i == (int)this->scheme.size()-1) {
                        if(i != (int)this->scheme.size()-1) {

                        }
                    }
                    else {
                        cout << ", ";
                    }
                }
            }
        }
    }

    
};

