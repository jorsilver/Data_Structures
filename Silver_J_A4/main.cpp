/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#include "ServiceCenter.h"

using namespace std;

int main(int argc, char const *argv[]){

    ServiceCenter serviceCenter(argv[1]);
    serviceCenter.simulate();

    return 0;
}
