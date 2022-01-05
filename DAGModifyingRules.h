
// include guard
#ifndef dag_modifying_rules_h
#define dag_modifying_rules_h

// 1st ---- its own header-file (it should be compilable without everything)
// nothing

// 2nd ---- headers written by me (it should be compilable without everything)
#include "DAG.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <vector>

class DAGModifyingRules {
    public:
        DAGModifyingRules(std::string pathToDAGModifyingRulesFile);
        ~DAGModifyingRules();
        void applyAllOfTheModifyingRulesOnADAG(DAG* d);
    private:
        std::string readFile(std::string pathToFile);
        void parseFile(std::string contentOfFile);
        std::vector<std::string> rules;
        char commentBeginningCharacter = '#';
        void applyRule1(DAG* d, std::string ruleToApply);
        void applyRule2(DAG* d, std::string ruleToApply);
        void applyRule3(DAG* d, std::string ruleToApply);
        void removeSubstring(std::string& str, std::string subStr);
    protected:

};

#endif // dag_modifying_rules_h
