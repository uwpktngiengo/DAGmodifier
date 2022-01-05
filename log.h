
// include guard
#ifndef log_h
#define log_h

// 1st ---- its own header-file (it should be compilable without everything)

// 2nd ---- headers written by me (it should be compilable without everything)

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>

enum logType{LOG, WARNING, ERROR};

class log {
    public:
        static void logThis(logType lt, std::string text);
    private:
        static const std::string currentDateTime(void);
    protected:

};

#endif // log_h
