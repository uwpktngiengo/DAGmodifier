
// 1st ---- its own header-file (it should be compilable without everything)
#include "log.h"

// 2nd ---- headers written by me (it should be compilable without everything)
// nothing

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <ios>
#include <fstream>

void log::logThis(logType lt, std::string text) {
    std::ofstream logFile("logfile.txt", std::ios_base::app | std::ios_base::out);

    switch(lt) {
        case LOG:
            std::cout << currentDateTime() << " LOG        [" << text << "]" << std::endl;
            logFile << currentDateTime() << " LOG        [" << text << "]\n";
        break;
        case WARNING:
            std::cout << currentDateTime() << " WARNING    [" << text << "]" << std::endl;
            logFile << currentDateTime() << " WARNING        [" << text << "]\n";
        break;
        case ERROR:
            std::cout << currentDateTime() << " ERROR      [" << text << "]" << std::endl;
            logFile << currentDateTime() << " ERROR        [" << text << "]\n";
        break;
    }
}

// Get current date/time, format is YYYY-MM-DD HH:mm:ss
const std::string log::currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}
