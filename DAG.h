
// include guard
#ifndef dag_h
#define dag_h

// 1st ---- its own header-file (it should be compilable without everything)
// nothing

// 2nd ---- headers written by me (it should be compilable without everything)
#include "DAGvertex.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <vector>

enum State{NORMAL1, VERTEXNAME, NORMAL2, FROMNAME, BETWEENFROMANDTO, TONAME};

class DAG {
    public:
        DAG(std::string dotGraphDescribingFilePath);
        ~DAG();
        void exportToFile(std::string outputFilePath);
        std::vector<DAGvertex> vertices;
        bool isThisVertexAlreadyStored(std::string id);
        void addVertex(std::string id);
        void removeEdgesWhichContainsThisVertex(std::string vertexID);
        void checkIntegrity();
    private:
        void addEdge(std::string Vertex1ID, std::string Vertex2ID);
        void parseGraphDotString(std::string str);
    protected:

};

#endif // dag_h
