#include "WGraph.cpp"
#include <iostream>
#include <fstream>
using namespace std;


WGraph* read_graph_from_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int size;
    infile >> size;

    WGraph *graph = new WGraph(size);

    // read the adjacency matrix from the file
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double w;
            infile >> w;
            if (w != 0.0) {
                graph->addEdge(i, j, w);
            }
        }
    }

    return graph;
}

int main(int argc, char ** argv){
    if(argc != 2) {
        throw runtime_error("Invalid no of arguments");
    }

    string filename = argv[1];
    WGraph *myWG = read_graph_from_file(filename);

    myWG->calcFW();
    myWG->computeMST();
//    cout << "cc 0 1: " << myWG->cheapestCost(0, 1) << endl;
    return 0;
}
