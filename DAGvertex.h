
// include guard
#ifndef dag_vertex_h
#define dag_vertex_h

// 1st ---- its own header-file (it should be compilable without everything)
// nothing

// 2nd ---- headers written by me (it should be compilable without everything)
#include "type.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <vector>
#include <string>

class DAGvertex {
    public:
        DAGvertex(std::string id);
        Type t;
        void addOutputVertex(std::string vertexID);
        std::vector<std::string> outputIDs;
    private:

    protected:

};

#endif // dag_vertex_h
