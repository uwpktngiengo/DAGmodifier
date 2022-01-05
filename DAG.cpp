
// 1st ---- its own header-file (it should be compilable without everything)
#include "DAG.h"

// 2nd ---- headers written by me (it should be compilable without everything)
#include "log.h"

// 3rd ---- 3rd-party headers (API, lib, SDK) (it should be compilable without standard C++ headers)
// nothing

// 4th ---- standard C++ headers
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

void DAG::parseGraphDotString(std::string graphStrDot) {
    enum State state;
    state = NORMAL1;

    std::string tempID = "";
    std::string tempVertex1ID = "";
    std::string tempVertex2ID = "";

    std::istringstream iss(graphStrDot);
    for (std::string line; std::getline(iss, line); ) {
        bool whiteSpacesOnly = std::all_of(line.begin(), line.end(), isspace);
        if(whiteSpacesOnly) {
            state = NORMAL2;
            continue;
        }
        for(auto it = line.cbegin(); it != line.cend(); ++it) {
            bool jumpToNextLine = false;
            switch(state) {
                case NORMAL1:
                    if(whiteSpacesOnly) {
                        state = NORMAL2;
                        jumpToNextLine = true; // jump to next line
                    }
                    else if(*it == '\"') {
                        state = VERTEXNAME;
                        tempID = "";
                    }
                break;
                case VERTEXNAME:
                    if(*it == '\"') {
                        state = NORMAL1;
                        addVertex(tempID);
                        tempID = "";
                        jumpToNextLine = true; // jump to next line
                    }
                    else {
                        tempID += (*it);
                    }
                break;
                case NORMAL2:
                    if(*it == '\"') {
                        state = FROMNAME;

                        tempVertex1ID = "";
                        tempVertex2ID = "";
                    }
                break;
                case FROMNAME:
                    if(*it == '\"') {
                        state = BETWEENFROMANDTO;
                    }
                    else {
                        tempVertex1ID += (*it);
                    }
                break;
                case BETWEENFROMANDTO:
                    if(*it == '\"') {
                        state = TONAME;
                    }
                break;
                case TONAME:
                    if(*it == '\"') {
                        state = NORMAL2;
                        addEdge(tempVertex1ID, tempVertex2ID);
                        tempVertex1ID = "";
                        tempVertex2ID = "";
                        jumpToNextLine = true; // jump to next line
                    }
                    else {
                        tempVertex2ID += (*it);
                    }
                break;
            }
            if(jumpToNextLine) {
                break;
            }
        }
    }
}

DAG::DAG(std::string dotGraphDescribingFilePath) { // the variable named "dotGraphDescribingFilePath" contains a path to a file, which file is written in "dot" language, which describes a graph, which is actually a DAG
    // open file and read its content
    std::ifstream t(dotGraphDescribingFilePath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string contentOfFile = buffer.str();

    // parse its content
    parseGraphDotString(contentOfFile);
}

DAG::~DAG() {

}

bool DAG::isThisVertexAlreadyStored(std::string id) {
    for(std::vector<DAGvertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        if(it->t.ID == id) { // already exists
            return true;
        }
    }
    return false;
}

void DAG::addVertex(std::string id) {
    log::logThis(LOG, "add vertex: " + id);
    bool alreadyAdded = isThisVertexAlreadyStored(id);
    if(!alreadyAdded) { // avoid duplicates
        DAGvertex dv(id);
        vertices.push_back(dv);
    }
}

void DAG::addEdge(std::string Vertex1ID, std::string Vertex2ID) { // add a directed edge from 1 to 2 (1 -> 2)
    log::logThis(LOG, "add edge: " + Vertex1ID + " -> " + Vertex2ID);
    addVertex(Vertex1ID); // if it is already added, it will do nothing
    addVertex(Vertex2ID); // if it is already added, it will do nothing

    // add 1->2 directed edge
    bool found = false;
    for(std::vector<DAGvertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        if(it->t.ID == Vertex1ID) {
            found = true;
            it->addOutputVertex(Vertex2ID);
            break;
        }
    }
    if(!found) {
        log::logThis(ERROR, "Tried to add an edge, could not find " + Vertex1ID + " vertex, which is an error, this should not happen.");
    }
}

void DAG::exportToFile(std::string outputFilePath) {
    std::string outputFileContent = "";

    outputFileContent += "digraph D {\n";
    for(std::vector<DAGvertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        outputFileContent += "  \"" + it->t.ID + "\"\n";
    }
    outputFileContent += "\n"; // empty line
    for(std::vector<DAGvertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        for(std::vector<std::string>::iterator it2 = it->outputIDs.begin(); it2 != it->outputIDs.end(); ++it2) {
            outputFileContent += "  \"" + it->t.ID + "\" -> \"" + (*it2) + "\"\n";
        }
    }
    outputFileContent += "}\n";

    std::ofstream fileHandler("theOutputFile.dot"); // TODO ez (is) legyen parameterezheto!!! (config fajl)
    fileHandler << outputFileContent;
    fileHandler.close();
}

void DAG::removeEdgesWhichContainsThisVertex(std::string vertexID) {
    for(std::vector<DAGvertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        for(std::vector<std::string>::iterator it2 = (it->outputIDs).begin(); it2 != (it->outputIDs).end(); ) {
            if((*it2) == vertexID) {
                it2 = (it->outputIDs).erase(it2); // delete edge
            }
            else {
                ++it2;
            }
        }
    }
}
