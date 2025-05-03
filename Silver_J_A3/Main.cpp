#include "SpeakerView.h"

//Main function creates a 'SpeakerView' object
//and calls its 'checkSeating()' function
int main(int argc, char *argv[]){
    try{
        SpeakerView sv1(argv[1]);
        sv1.checkSeating();
    }
    catch(runtime_error &excpt){
        cout << excpt.what() << endl;
    }
    return 0;
}