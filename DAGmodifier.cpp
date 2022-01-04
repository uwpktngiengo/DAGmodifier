
// 1st ---- its own header-file (it should be compilable without everything)
#include "DAGmodifier.h"

// 2nd ---- headers written by me (it should be compilable without everything)
// nothing

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
// nothing

void DAGmodifier::DAGmodifierAlgorithm(void) {
    std::cout << "program start" << std::endl;
    /// TODO system("graphviz\\dot.exe -Tpng abc.dot -o krumpli.png");

    // az alábbit beletenni egy Algorithm::algirthm() függvénybe!
    // legyen paraméterezhetõ, config-olható, mondjuk egy config-fájlból!

    Graph gr;
    gr.openFile("inputGraph.dot"); // dot language
    gr.generateImage("inputGraphDrawing.png"); // generate png image file

    GraphModifyingRules gmr;
    gmr.openFile("rules.dat"); // my own custom rule-describing "language"

    gr.applyModifyingRules(gmr);
    gr.exportToFile("outputGraph.dot"); // dot language
    gr.generateImage("outputGraphDrawing.png"); // generate png image file

    std::cout << "program end" << std::endl;
}
