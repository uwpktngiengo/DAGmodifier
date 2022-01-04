
// 1st ---- its own header-file (it should be compilable without everything)
#include "type.h"

// 2nd ---- headers written by me (it should be compilable without everything)
// nothing

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <algorithm>

Type::~Type() {}

Type::Type() {
    ID = "";
    type = "";
}

Type::Type(std::string id) {
    ID = id; // for example: 29_B
    type = convertIDIntoType(id); // for example: B
}

std::string Type::convertIDIntoType(std::string theID) {
    int pos = theID.find("_") + 1; // for example: 29_B
    if(pos == 0) { // there is no '_' character in the string named "theID"
        // TODO warning!
    }

    size_t n = std::count(theID.begin(), theID.end(), '_');
    if(n != 1) {
        // TODO warning!
    }

    return theID.substr(pos); // for example: B
}
