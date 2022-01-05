
// include guard
#ifndef config_h
#define config_h

// 1st ---- its own header-file (it should be compilable without everything)
// nothing

// 2nd ---- headers written by me (it should be compilable without everything)
// nothing

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>

class config {
    public:
        static void processConfigFile(std::string pathToConfigFile);

        static bool drawGraphImagesEnabled;
        static std::string drawGraphImageExternalProgramPath;
        static std::string inputFilePath;
        static std::string outputFilePath;
        static std::string inputFileDrawImagePath;
        static std::string outputFileDrawImagePath;
        static std::string logfilePath;
        static std::string modifyingRulesFilePath;

    private:

    protected:

};

#endif // config_h
