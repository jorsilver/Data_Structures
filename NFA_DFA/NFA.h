#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class NFA
{
public:
    NFA();
    NFA(const string& inputFile);
    //~NFA();
    //void generateDFA();
    void printNFA();
private:
    string startState;
    map<string, int> stateMap;
    map<string, int> symbolMap;
    vector<int> acceptStates;
    vector<vector<vector<int> > > transitionTable;

    void fileToTable(ifstream& inputFile);
    //void closure();
};
#endif