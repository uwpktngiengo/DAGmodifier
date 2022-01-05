
// include guard
#ifndef type_h
#define type_h

// 1st ---- its own header-file (it should be compilable without everything)
// nothing

// 2nd ---- headers written by me (it should be compilable without everything)
// nothing

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>

class Type {
    public:
        Type();
        Type(std::string id);
        ~Type();
        std::string ID; // for example: 29_B
        std::string type; // for example: B
        static std::string convertIDIntoType(std::string theID); // 29_B -> B
        void operator=(const Type &t);
    private:

    protected:

};

#endif // type_h
