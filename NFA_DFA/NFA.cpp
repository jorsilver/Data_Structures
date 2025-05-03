#include "NFA.h"

NFA::NFA(){
    // Implement the default constructor if needed
}


NFA::NFA(const string& inputFile){
    ifstream fileInStream(inputFile);
    if (!fileInStream) throw runtime_error("The input file could not be opened");

    fileToTable(fileInStream);

    fileInStream.close();
}

void NFA::fileToTable(ifstream& fileInStream){
    int lineNum = 1;
    string line;
    symbolMap["EPS"] = 0; // Hardcoding Epsilon to index 0
    while (getline(fileInStream, line) && line != "END") {
        istringstream stringStream(line);
        if (lineNum < 5){
            int index = 0;
            string cell;
            while (stringStream >> cell){
                if (lineNum == 1){ // State alphabet
                    stateMap[cell] = index++;
                } else if (lineNum == 2){ // Input alphabet
                    symbolMap[cell] = ++index; // Preincrement to offset "EPS" -> 0
                } else if (lineNum == 3){ // Start state
                    startState = cell;
                } else { // Line 4 - Accept states
                    acceptStates.push_back(stateMap[cell]);
                }
            }
            ++lineNum;
        } else if (lineNum++ > 5){
            if (transitionTable.size() != stateMap.size()){
                transitionTable.resize(stateMap.size()); // The first axis represents all the start states
                for (vector<vector<int> >& state : transitionTable){
                    state.resize(symbolMap.size()); // initialize the 2nd dimension vector for each state, consisting of all posible inputs
                }
            }

            string fromState, symbolRead, toState, ignore;
            getline(stringStream, fromState, ',');
            stringStream >> ws >> symbolRead >> ignore >> ws >> toState;

            transitionTable[stateMap[fromState]][symbolMap[symbolRead]].push_back(stateMap[toState]); // Add the end state from the current line as a new index in the 3rd dimension for the corresponding start state and input
        }
    }

    for (size_t i = 0; i < transitionTable.size(); ++i) {
        for (size_t j = 0; j < transitionTable[i].size(); ++j) {
            for (size_t k = 0; k < transitionTable[i][j].size(); ++k) {
                std::cout << transitionTable[i][j][k] << " ";
            }
            std::cout << std::endl; // Newline after printing each row
        }
        std::cout << std::endl; // Newline after printing each 2D layer
    }
}

void NFA::printNFA(){
    // Print Transition Table
    cout << "Transition Table:" << endl;
    for (const auto& state : stateMap) {
        for (const auto& symbol : symbolMap) {
            cout << state.first << " -" << symbol.first << "-> ";
            for (const auto& nextState : transitionTable[state.second][symbol.second]) {
                for (const auto& nextStatePair : stateMap) {
                    if (nextStatePair.second == nextState) {
                        cout << nextStatePair.first << " ";
                    }
                }
            }
            cout << endl;
        }
    }
}













    // // Print the populated transition table
    // cout << "Transition Table:" << endl;
    // for (const auto& statePair : stateMap) {
    //     int stateIndex = statePair.second;
    //     for (const auto& symbolPair : symbolMap) {
    //         int symbolIndex = symbolPair.second;
    //         cout << "Delta(" << statePair.first << ", " << symbolPair.first << ") = { ";
    //         for (int nextState : transitionTable[stateIndex][symbolIndex]) {
    //             cout << nextState << " ";
    //         }
    //         cout << "}" << endl;
    //     }
    // }