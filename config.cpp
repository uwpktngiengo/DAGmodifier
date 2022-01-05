
// 1st ---- its own header-file (it should be compilable without everything)
#include "config.h"

// 2nd ---- headers written by me (it should be compilable without everything)
#include "log.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <sstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

bool config::drawGraphImagesEnabled;
std::string config::drawGraphImageExternalProgramPath;
std::string config::inputFilePath;
std::string config::outputFilePath;
std::string config::inputFileDrawImagePath;
std::string config::outputFileDrawImagePath;
std::string config::logfilePath;
std::string config::modifyingRulesFilePath;

void config::processConfigFile(std::string pathToConfigFile) {
    // open file and read its content
    std::ifstream t(pathToConfigFile);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string contentOfFile = buffer.str();

    std::istringstream iss(contentOfFile);
    for(std::string line; std::getline(iss, line); ) {
        bool whiteSpacesOnly = std::all_of(line.begin(), line.end(), isspace);
        if(whiteSpacesOnly) {
            continue;
        }
        else if(line.rfind("drawGraphImagesEnabled", 0) == 0) {
            line.erase(0, 25); // remove first 25 chars
            if(line == "true") {
                drawGraphImagesEnabled = true;
                log::logThis(LOG, "Config -> drawGraphImagesEnabled = true");
            }
            else if(line == "false") {
                drawGraphImagesEnabled = false;
                log::logThis(LOG, "Config -> drawGraphImagesEnabled = false");
            }
            else {
                drawGraphImagesEnabled = false; // some kind of default value
                log::logThis(WARNING, "In the config-file, drawGraphImagesEnabled has an unknown value(" + line + ").");
                log::logThis(LOG, "Config -> drawGraphImagesEnabled = false (default value)");
            }
        }
        else if(line.rfind("drawGraphImageExternalProgramPath", 0) == 0) {
            line.erase(0, 36);
            drawGraphImageExternalProgramPath = line;
            log::logThis(LOG, "Config -> drawGraphImageExternalProgramPath = " + line);
        }
        else if(line.rfind("inputFilePath", 0) == 0) {
            line.erase(0, 16);
            inputFilePath = line;
            log::logThis(LOG, "Config -> inputFilePath = " + line);
        }
        else if(line.rfind("outputFilePath", 0) == 0) {
            line.erase(0, 17);
            outputFilePath = line;
            log::logThis(LOG, "Config -> outputFilePath = " + line);
        }
        else if(line.rfind("inputFileDrawImagePath", 0) == 0) {
            line.erase(0, 25);
            inputFileDrawImagePath = line;
            log::logThis(LOG, "Config -> inputFileDrawImagePath = " + line);
        }
        else if(line.rfind("outputFileDrawImagePath", 0) == 0) {
            line.erase(0, 26);
            outputFileDrawImagePath = line;
            log::logThis(LOG, "Config -> outputFileDrawImagePath = " + line);
        }
        else if(line.rfind("logfilePath", 0) == 0) {
            line.erase(0, 14);
            logfilePath = line;
            log::logThis(LOG, "Config -> logfilePath = " + line);
        }
        else if(line.rfind("modifyingRulesFilePath", 0) == 0) {
            line.erase(0, 25);
            modifyingRulesFilePath = line;
            log::logThis(LOG, "Config -> modifyingRulesFilePath = " + line);
        }
        else {
            log::logThis(WARNING, "Unknown row in config-file.");
        }
    }
}
