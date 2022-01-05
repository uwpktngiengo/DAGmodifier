
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

// TODO std::cin, API, paraméteres programindítás, stb.

int main(int argc, char** argv) {
    // This program is a "rule based graph modifier", written in C++.

    config::processConfigFile("config.data");

    log::logThis(LOG, "program start");
    DAGmodifier::DAGmodifierAlgorithm();
    log::logThis(LOG, "program end");

    return 0;
}

// TODO -> leírni a dokumentációba, hogy a "dot" nyelvnek én egy általam kitalált, szigorított/szűkített változatát használom, és hogy a bemenethez képest a kimenet szegényesebb lesz (pl. a formázások eltűnnek)
// TODO -> azt is beleírni a dokumentációba, hogy ha nem változtatunk semmit, a kimeneti gráf akkor is más lesz leírónyelvileg (eltűnnek a formázások, és az elején minden csúcs fel lesz sorolva, nem csak néhány) (és rajzilag is, mert eltűnnek a formázások)

// TODO API, fájlból beolvasás, paraméteres programindítás, std::cin-nel történő beolvasás, stb...
