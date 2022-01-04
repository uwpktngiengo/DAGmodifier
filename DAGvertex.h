
// include guard
#ifndef dag_vertex_h
#define dag_vertex_h

// 1st ---- its own header-file (it should be compilable without everything)
// nothing

// 2nd ---- headers written by me (it should be compilable without everything)
// nothing

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
// nothing

class DAGvertex {
    public:
        DAGvertex(std::string id);
        ~DAGvertex();
        Type t;
    private:
        std::vector<DAGvertex *> outputs;

    protected:

};

#endif // dag_vertex_h
