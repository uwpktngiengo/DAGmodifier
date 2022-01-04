
// 1st ---- its own header-file (it should be compilable without everything)
#include "graphModifyingRules.h"

// 2nd ---- headers written by me (it should be compilable without everything)
#include "type.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

GraphModifyingRules::~GraphModifyingRules() {

}

GraphModifyingRules::GraphModifyingRules(std::string pathToGraphModifyingRulesFile) {
    std::string contentOfFile = readFile(pathToGraphModifyingRulesFile);
    parseFile(contentOfFile);
}

std::string GraphModifyingRules::readFile(std::string pathToFile) {
    std::ifstream t(pathToFile);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void GraphModifyingRules::parseFile(std::string contentOfFile) {
    std::istringstream iss(contentOfFile);
    for (std::string line; std::getline(iss, line); ) {
        std::size_t found = line.find_first_not_of(" \t"); // first non-whitespace
        if(found != std::string::npos) {
            if(line.at(found) == commentBeginningCharacter) { // comment line, do nothing

            }
            else { // normal line
                rules.push_back(line);
            }
        }
        else { // only whitespaces in this line, do nothing

        }
    }
}

void GraphModifyingRules::applyAllOfTheModifyingRulesOnADAG(DAG* d) {
    for(std::vector<std::string>::iterator it = rules.begin(); it != rules.end(); ++it) {
        if((*it).rfind("ruleType1 replaceTriplet ", 0) == 0) {
            applyRule1(d, *it);
        }
        else if((*it).rfind("ruleType2 insertBetweenTheseTwo: ", 0) == 0) {
            applyRule2(d, *it);
        }
        else if((*it).rfind("ruleType3 ", 0) == 0) {
            applyRule3(d, *it);
        }
        else {
            // TODO error log, unknown type of rule
        }
    }
}

void GraphModifyingRules::applyRule1(DAG* d, std::string ruleToApply) {
    // TODO figyelni az ID-kra, ha valamelyik szám már foglalt, akkor megnövelni a számot!!!
    ruleToApply.erase(ruleToApply.begin(), std::find_if(ruleToApply.begin(), ruleToApply.end(), std::bind1st(std::not_equal_to<char>(), ' '))); // remove leading whitespaces
    ruleToApply.erase(std::find_if(ruleToApply.rbegin(), ruleToApply.rend(), std::bind1st(std::not_equal_to<char>(), ' ')).base(), ruleToApply.end()); // remove trailing whitespaces

    std::string firstType = "";
    std::string secondType = "";
    std::string thirdType = "";

    std::string newType = "";

    std::string newInputIsThisOnesInput = "";
    std::string newOutputIsThisOnesOutput = "";

    ruleToApply.erase(0, 25); // remove first 25 chars

    // now it looks like something like this:    "A B C with X (input: A, output: C)"

    removeSubstring(ruleToApply, "with ");
    removeSubstring(ruleToApply, "(input: ");
    removeSubstring(ruleToApply, ", output:");
    removeSubstring(ruleToApply, ")");

    // now it looks like something like this:    "A B C X A C"    (Note: each could be longer than 1 character. This is why it is not parsed by the given character's position. We couldn't tell, how many characters long is it, the only one thing we know that they are separated by spaces.)

    int state = 0;
    for(auto it = ruleToApply.cbegin(); it != ruleToApply.cend(); ++it) {
        switch(state) {
            case 0:
                if((*it) == ' ') {
                    state++;
                }
                else {
                    firstType += (*it); // append a character
                }
            break;
            case 1:
                if((*it) == ' ') {
                    state++;
                }
                else {
                    secondType += (*it); // append a character
                }
            break;
            case 2:
                if((*it) == ' ') {
                    state++;
                }
                else {
                    thirdType += (*it); // append a character
                }
            break;
            case 3:
                if((*it) == ' ') {
                    state++;
                }
                else {
                    newType += (*it); // append a character
                }
            break;
            case 4:
                if((*it) == ' ') {
                    state++;
                }
                else {
                    newInputIsThisOnesInput += (*it); // append a character
                }
            break;
            case 5:
                if(((*it) == ' ') || ((*it) == '\n') || ((*it) == '\r') || ((*it) == '\t')) {
                    state++; // state 6 is a non-existing, do-nothing-at-all state :-)
                }
                else {
                    newOutputIsThisOnesOutput += (*it); // append a character
                }
            break;
        }
    }

    int howManyTimesApplied = 0; // Note: this could be more than one, and it is also possible to be zero.
    for(std::vector<DAGvertex>::iterator it = (d->vertices).begin(); it != (d->vertices).end(); ++it) {
        if((it->t.type) == firstType) {
            for(std::vector<std::string>::iterator it2 = (it->outputIDs).begin(); it2 != (it->outputIDs).end(); ++it2) {
                std::string theTyp = Type::convertIDIntoType(*it2); // 29_B -> B
                if(theTyp == secondType) {

                    for(std::vector<DAGvertex>::iterator it3 = (d->vertices).begin(); it3 != (d->vertices).end(); ++it3) {
                        if(it3->t.ID == (*it2)) {
                            for(std::vector<std::string>::iterator it4 = (it3->outputIDs).begin(); it4 != (it3->outputIDs).end(); ++it4) {
                                std::string theTyp2 = Type::convertIDIntoType(*it4); // 29_B -> B
                                if(theTyp2 == thirdType) {
                                    howManyTimesApplied++;
                                    // TODO végrehajtani a módosítást
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    std::cout << "Rule-1 applied this many times: [" << howManyTimesApplied << "]." << std::endl; // TODO logrendszer!!!
}

void GraphModifyingRules::applyRule2(DAG* d, std::string ruleToApply) {
    // TODO figyelni az ID-kra, ha valamelyik szám már foglalt, akkor megnövelni a számot!!!
    ruleToApply.erase(ruleToApply.begin(), std::find_if(ruleToApply.begin(), ruleToApply.end(), std::bind1st(std::not_equal_to<char>(), ' '))); // remove leading whitespaces
    ruleToApply.erase(std::find_if(ruleToApply.rbegin(), ruleToApply.rend(), std::bind1st(std::not_equal_to<char>(), ' ')).base(), ruleToApply.end()); // remove trailing whitespaces

    std::string firstType = "";
    std::string secondType = "";

    std::string newType = "";

    ruleToApply.erase(0, 33); // remove first 33 chars

    // now it looks like something like this:    "D E this: Y"

    removeSubstring(ruleToApply, "this: ");

    // now it looks like something like this:    "D E Y"    (Note: each could be longer than 1 character. This is why it is not parsed by the given character's position. We couldn't tell, how many characters long is it, the only one thing we know that they are separated by spaces.)

    int state = 0;
    for(auto it = ruleToApply.cbegin(); it != ruleToApply.cend(); ++it) {
        switch(state) {
            case 0:
                if((*it) == ' ') {
                    state++;
                }
                else {
                    firstType += (*it); // append a character
                }
            break;
            case 1:
                if((*it) == ' ') {
                    state++;
                }
                else {
                    secondType += (*it); // append a character
                }
            break;
            case 2:
                if(((*it) == ' ') || ((*it) == '\n') || ((*it) == '\r') || ((*it) == '\t')) {
                    state++; // state 3 is a non-existing, do-nothing-at-all state :-)
                }
                else {
                    newType += (*it); // append a character
                }
            break;
        }
    }

    int howManyTimesApplied = 0; // Note: this could be more than one, and it is also possible to be zero.
    for(std::vector<DAGvertex>::iterator it = (d->vertices).begin(); it != (d->vertices).end(); ++it) {
        if((it->t.type) == firstType) {
            for(std::vector<std::string>::iterator it2 = (it->outputIDs).begin(); it2 != (it->outputIDs).end(); ++it2) {
                std::string theTyp = Type::convertIDIntoType(*it2); // 29_B -> B
                if(theTyp == secondType) {
                    howManyTimesApplied++;

                    std::string oldEVertexID = (*it2);

                    (it->outputIDs).erase(it2); // remove D->E directed edge

                    // add new Y vertex
                    std::string theFinalYID = "";
                    while(true) {
                        unsigned int i = 1;
                        std::string number = std::to_string(i);

                        bool alreadyTaken = d->isThisVertexAlreadyStored(number + "_Y"); // for example: "1_Y" or "17_Y"
                        if(!alreadyTaken) {
                            d->addVertex(number + "_Y"); // for example: "1_Y" or "17_Y"
                            theFinalYID = number + "_Y";
                            break; // exit the infinite while-loop
                        }
                        i++; // jump to the next possible Y, maybe that one is not already taken
                    }

                    // add new D->Y directed edge
                    (it->outputIDs).push_back(theFinalYID);

                    // add new Y->E directed edge
                    if(((d->vertices).back()).t.ID != theFinalYID) { /* TODO log error! */ }
                    ((d->vertices).back()).outputIDs.push_back(oldEVertexID);
                }
            }
        }
    }
    std::cout << "Rule-2 applied this many times: [" << howManyTimesApplied << "]." << std::endl; // TODO logrendszer!!!
}

void GraphModifyingRules::applyRule3(DAG* d, std::string ruleToApply) {
    // TODO figyelni az ID-kra, ha valamelyik szám már foglalt, akkor megnövelni a számot!!!
    ruleToApply.erase(ruleToApply.begin(), std::find_if(ruleToApply.begin(), ruleToApply.end(), std::bind1st(std::not_equal_to<char>(), ' '))); // remove leading whitespaces
    ruleToApply.erase(std::find_if(ruleToApply.rbegin(), ruleToApply.rend(), std::bind1st(std::not_equal_to<char>(), ' ')).base(), ruleToApply.end()); // remove trailing whitespaces

    // TODO implementálni
}

void GraphModifyingRules::removeSubstring(std::string& str, std::string subStr) {
    std::string::size_type i = str.find(subStr);
    if(i != std::string::npos) {
        str.erase(i, subStr.length());
    }
}
