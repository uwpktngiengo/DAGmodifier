
// 1st ---- its own header-file (it should be compilable without everything)
#include "DAGModifyingRules.h"

// 2nd ---- headers written by me (it should be compilable without everything)
#include "type.h"
#include "log.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>

DAGModifyingRules::~DAGModifyingRules() {

}

DAGModifyingRules::DAGModifyingRules(std::string pathToDAGModifyingRulesFile) {
    std::string contentOfFile = readFile(pathToDAGModifyingRulesFile);
    parseFile(contentOfFile);
}

std::string DAGModifyingRules::readFile(std::string pathToFile) {
    std::ifstream t(pathToFile);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void DAGModifyingRules::parseFile(std::string contentOfFile) {
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

void DAGModifyingRules::applyAllOfTheModifyingRulesOnADAG(DAG* d) {
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
            log::logThis(WARNING, "Unknown type of rule.");
        }
    }
}

void DAGModifyingRules::applyRule1(DAG* d, std::string ruleToApply) {
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
    START_OVER:
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

                                    std::string theGivenA = (it->t.ID);
                                    std::string theGivenB = (*it2);
                                    std::string theGivenC = (*it4);

                                    // add new X-type vertex
                                    log::logThis(LOG, "apply rule 1, add new X-type vertex");
                                    std::string theFinalXID = "";
                                    while(true) {
                                        unsigned int i = 1;
                                        std::string number = std::to_string(i);

                                        bool alreadyTaken = d->isThisVertexAlreadyStored(number + "_X"); // for example: "1_X" or "17_X"
                                        if(!alreadyTaken) {
                                            d->addVertex(number + "_X"); // for example: "1_X" or "17_X"
                                            theFinalXID = number + "_X";
                                            break; // exit the infinite while-loop
                                        }
                                        i++; // jump to the next possible X, maybe that one is not already taken
                                    }
                                    log::logThis(LOG, "new X vertex's name: " + theFinalXID);

                                    // add A's inputs to X
                                    log::logThis(LOG, "apply rule 1, add A's inputs to X (A: " + theGivenA + ")");
                                    int skipThisMany = 0;
                                    AGAIN:
                                    int i = 0;
                                    for(std::vector<DAGvertex>::iterator it5 = (d->vertices).begin(); it5 != (d->vertices).end(); ++it5) {
                                        for(std::vector<std::string>::iterator it6 = (it5->outputIDs).begin(); it6 != (it5->outputIDs).end(); ++it6) {
                                            if((*it6) == theGivenA) {
                                                i++;
                                                if(i > skipThisMany) {
                                                    it5->outputIDs.push_back(theFinalXID);
                                                    skipThisMany++;
                                                    goto AGAIN;
                                                }
                                            }
                                        }
                                    }

                                    // add C's outputs to X
                                    log::logThis(LOG, "apply rule 1, add C's outputs to X (C: " + theGivenC + ")");
                                    skipThisMany = 0;
                                    AGAIN2:
                                    i = 0;
                                    for(std::vector<DAGvertex>::iterator it5 = (d->vertices).begin(); it5 != (d->vertices).end(); ++it5) {
                                        if((it5->t.ID) == theGivenC) {
                                            i++;
                                            if(i > skipThisMany) {
                                                if(((d->vertices).back()).t.ID != theFinalXID) { log::logThis(ERROR, "Impossible case. This should not happen."); }
                                                ((d->vertices).back()).outputIDs.insert(std::end(((d->vertices).back()).outputIDs), std::begin(it5->outputIDs), std::end(it5->outputIDs));
                                                skipThisMany++;
                                                goto AGAIN2;
                                            }
                                        }
                                    }

                                    // remove the appropriate A-type vertex
                                    log::logThis(LOG, "apply rule 1, remove appropriate A-type vertex: " + theGivenA);
                                    for(std::vector<DAGvertex>::iterator it128 = (d->vertices).begin(); it128 != (d->vertices).end(); ) {
                                        if((it128->t.ID) == theGivenA) {
                                            it128 = (d->vertices).erase(it128);
                                            log::logThis(LOG, "(A) delete " + theGivenA + " vertex");
                                            break;
                                        }
                                        else {
                                            ++it128;
                                        }
                                    }
                                    d->removeEdgesWhichContainsThisVertex(theGivenA);

                                    // remove the appropriate B-type vertex
                                    log::logThis(LOG, "apply rule 1, remove appropriate B-type vertex: " + theGivenB);
                                    for(std::vector<DAGvertex>::iterator it128 = (d->vertices).begin(); it128 != (d->vertices).end(); ) {
                                        if((it128->t.ID) == theGivenB) {
                                            it128 = (d->vertices).erase(it128);
                                            log::logThis(LOG, "(B) delete " + theGivenB + " vertex");
                                            break;
                                        }
                                        else {
                                            ++it128;
                                        }
                                    }
                                    d->removeEdgesWhichContainsThisVertex(theGivenB);

                                    // remove the appropriate C-type vertex
                                    log::logThis(LOG, "apply rule 1, remove appropriate C-type vertex: " + theGivenC);
                                    for(std::vector<DAGvertex>::iterator it128 = (d->vertices).begin(); it128 != (d->vertices).end(); ) {
                                        if((it128->t.ID) == theGivenC) {
                                            it128 = (d->vertices).erase(it128);
                                            log::logThis(LOG, "(C) delete " + theGivenC + " vertex");
                                            break;
                                        }
                                        else {
                                            ++it128;
                                        }
                                    }
                                    d->removeEdgesWhichContainsThisVertex(theGivenC);

                                    goto START_OVER; // start over, because the data-structure changed (some of its elements are erased)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    log::logThis(LOG, "Rule-1 applied this many times: [" + std::to_string(howManyTimesApplied) + "].");
}

void DAGModifyingRules::applyRule2(DAG* d, std::string ruleToApply) {
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
                    if(((d->vertices).back()).t.ID != theFinalYID) { log::logThis(ERROR, "Impossible case. This should not happen."); }
                    ((d->vertices).back()).outputIDs.push_back(oldEVertexID);
                }
            }
        }
    }
    log::logThis(LOG, "Rule-2 applied this many times: [" + std::to_string(howManyTimesApplied) + "].");
}

void DAGModifyingRules::applyRule3(DAG* d, std::string ruleToApply) {
    // TODO In case we add new vertices, we should take care of numbers in IDs, because if it is already taken, number should increment.
    ruleToApply.erase(ruleToApply.begin(), std::find_if(ruleToApply.begin(), ruleToApply.end(), std::bind1st(std::not_equal_to<char>(), ' '))); // remove leading whitespaces
    ruleToApply.erase(std::find_if(ruleToApply.rbegin(), ruleToApply.rend(), std::bind1st(std::not_equal_to<char>(), ' ')).base(), ruleToApply.end()); // remove trailing whitespaces

    // TODO implement this function
}

void DAGModifyingRules::removeSubstring(std::string& str, std::string subStr) {
    std::string::size_type i = str.find(subStr);
    if(i != std::string::npos) {
        str.erase(i, subStr.length());
    }
}
