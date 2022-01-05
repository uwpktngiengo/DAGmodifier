
// 1st ---- its own header-file (it should be compilable without everything)
#include "DAGmodifier.h"

// 2nd ---- headers written by me (it should be compilable without everything)
#include "DAG.h"
#include "DAGModifyingRules.h"
#include "config.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <cstdlib>

void DAGmodifier::DAGmodifierAlgorithm(void) {
    if(config::drawGraphImagesEnabled) {
        std::string cmd = config::drawGraphImageExternalProgramPath + " -Tpng " + config::inputFilePath + " -o " + config::inputFileDrawImagePath;
        system(cmd.c_str());
    }

    DAG* dag = new DAG(config::inputFilePath);

    DAGModifyingRules gmr(config::modifyingRulesFilePath);
    gmr.applyAllOfTheModifyingRulesOnADAG(dag);

    dag->exportToFile(config::outputFilePath);

    if(config::drawGraphImagesEnabled) {
        std::string cmd = config::drawGraphImageExternalProgramPath + " -Tpng " + config::outputFilePath + " -o " + config::outputFileDrawImagePath;
        system(cmd.c_str());
    }

    delete dag;
    dag = NULL; // just to be sure :-)
}
