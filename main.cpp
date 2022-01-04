
// 1st ---- its own header-file (it should be compilable without everything)
// nothing

// 2nd ---- headers written by me (it should be compilable without everything)
// nothing

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    DAGmodifier::DAGmodifierAlgorithm();
    return 0;
}

// TODO dokumentáció-írás, log kezelő (log, warning, error, esetleg színkezelés), config fájlban beállítások
