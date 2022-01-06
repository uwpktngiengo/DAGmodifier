
// 1st ---- its own header-file (it should be compilable without everything)
// nothing

// 2nd ---- headers written by me (it should be compilable without everything)
#include "DAGmodifier.h"
#include "log.h"
#include "config.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
// nothing

int main(int argc, char** argv) {
    // This program is a "rule based graph modifier", written in C++.

    config::processConfigFile("config.data");

    log::logThis(LOG, "program start");
    DAGmodifier::DAGmodifierAlgorithm();
    log::logThis(LOG, "program end");

    return 0;
}

// TODO a dokumentacioba tenni kepet a bemeno es kimeno graf legeneralt rajzarol!
// TODO az eredeti bemeneti gráf helyett kitalálni egy másikat
