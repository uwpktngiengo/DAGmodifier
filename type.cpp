
// 1st ---- its own header-file (it should be compilable without everything)
#include "type.h"

// 2nd ---- headers written by me (it should be compilable without everything)
// nothing

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <algorithm>

Type::Type(std::string id) {
    ID = id; // for example: 29_B
    int pos = id.find("_") + 1;
    if(pos == 0) { // there is no '_' character in the string named "id"
        // TODO warning!
    }

    size_t n = std::count(id.begin(), id.end(), '_');
    if(n != 1) {
        // TODO warning!
    }

    type = id.substr(pos); // for example: B
}
