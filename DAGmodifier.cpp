
// 1st ---- its own header-file (it should be compilable without everything)
#include "DAGmodifier.h"

// 2nd ---- headers written by me (it should be compilable without everything)
#include "DAG.h"
#include "DAGModifyingRules.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <cstdlib>

void DAGmodifier::DAGmodifierAlgorithm(void) {
    system("graphviz\\dot.exe -Tpng theInputFile.dot -o theInputDAG.png"); // TODO ez (is) legyen parameterezheto!!!

    // TODO config-fájl

    DAG* dag = new DAG("theInputFile.dot");

    DAGModifyingRules gmr("theRulesToApply.data"); // TODO a fájlpath paraméterezhetõ legyen (config fájl, std::cin, API, paraméteres programindítás, stb.)
    gmr.applyAllOfTheModifyingRulesOnADAG(dag);

    dag->exportToFile("theOutputFile.dot");
    system("graphviz\\dot.exe -Tpng theOutputFile.dot -o theOutputDAG.png"); // TODO ez (is) legyen parameterezheto!!!

    delete dag;
    dag = NULL;
}
