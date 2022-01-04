
// 1st ---- its own header-file (it should be compilable without everything)
#include "DAGvertex.h"

// 2nd ---- headers written by me (it should be compilable without everything)
#include "type.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <algorithm>
#include <string>
#include <vector>

DAGvertex::DAGvertex(std::string id) {
    Type typ(id);
    t = typ;

    std::vector<std::string> outputIDs_; // TODO
    outputIDs = outputIDs_; // TODO
}

void DAGvertex::addOutputVertex(std::string vertexID) {
    if(std::find(outputIDs.begin(), outputIDs.end(), vertexID) == outputIDs.end()) { // it is not here
        outputIDs.push_back(vertexID); // add
    }
}
