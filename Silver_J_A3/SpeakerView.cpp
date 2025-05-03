#include "SpeakerView.h"

//Constructor opens the file passed in and
//checks how many rows and columns are in the file.
//Then creates an array from those dimensions and
//populates the array with the values in the file.
SpeakerView::SpeakerView(const string& input): rows(0), cols(0){

    ifstream fileInStream(input);

    if (!fileInStream) throw runtime_error("The input file could not be opened");

    string line;
    double cell;

    //Count rows and cols
    while (getline(fileInStream, line)){//iterate through each line in the file.
        if (rows++ == 0){//count the columns on the first line only.
            stringstream ss(line);
            while (ss >> cell) ++cols;//iterate through each value on the current line to count the columns
        }
    }

    //Initialize 'cellArr' to an array of length 'rows' * 'cols'
    cellArr = new double[rows * cols];

    //Populate the array
    fileInStream.clear();
    fileInStream.seekg(0);//point the file stream back to the beginning of the file.
    int i = 0;
    while (getline(fileInStream, line)){//iterate through each line in the file.
        int j = 0;
        stringstream ss(line);
        while (ss >> cell){//iterate through each value on the current line.
            cellArr[i * cols + j] = cell;//add the current value to the array.
            j++;
        }
        i++;
    }

    fileInStream.close();
}

//Checks the seating chart and displays to terminal how
//many people in each column can see the speaker.
void SpeakerView::checkSeating(){

    for (int j = 0; j < cols; ++j){//iterate through the array columns then rows.
        MonoStack<double> stack(rows, 'd');//make a stack for each column.
        for (int i = rows - 1; i >= 0; --i){
            //push each value in the column to the stack. if the value pushed before the
            //current value is smaller than the current value it will be popped from the stack.
            stack.push(cellArr[i * cols + j]);
        }//all values remaining on the stack after the loop has ended can see the speaker.
        cout << endl << stack.size() << " person(s) can see in column "
            << j + 1 << "\nTheir heights are:\n";
        while(!stack.isEmpty()){
            cout << stack.pop() << " inches\n";
        }
    }
}

SpeakerView::~SpeakerView(){
    delete[] cellArr;
}