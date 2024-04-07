// Stephen Sallas sms0107
// Project 3: File I/O
// Compiled on Auburn Engineering ssh using g++ project3_Sallas_sms0107.cpp -o p3 THEN ./p3

// Learned how to use the sort method from the algorithm library from https://www.cplusplus.com/articles/NhA0RXSz/
// This was used on line 10 and line 147

#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

/**************************************************************************************/
/**************************** Global Variables ****************************************/
/**************************************************************************************/
const int MAX_SIZE = 100;

/**************************************************************************************/
/**************************** Prototypes **********************************************/
/**************************************************************************************/
int readfile(int inputArray[], ifstream& instream);

int sort(int inputArray1[], int inputArray1_size,
    int inputArray2[], int inputArray2_size, int outputArray[]);

void writefile(int outputArray[], int outputArray_size, string outfile);

/**************************************************************************************/
/**************************** Main  ***************************************************/
/**************************************************************************************/
int main() {
    // Variables
    ifstream instream;
    string infile;
    string outfile;
    int Array1[MAX_SIZE];
    int Array1_size;
    int Array2[MAX_SIZE];
    int Array2_size;
    int outputArray[MAX_SIZE];
    int outputArray_size;

    // Inputting first file
    cout << "***Welcome to Stephen's sorting program***\n";
    cout << "Enter the first input file name: ";
    cin >> infile;
    instream.open((char*)infile.c_str());

    // Error handling
    if (instream.fail()) {
        cout << "Input file opening failed.\n";
        return 0;
    }

    // Using readfile function to find array 1 size
    Array1_size = readfile(Array1, instream);

    // Closing the first file stream
    instream.close();

    // Outputting numbers
    cout << "The list of " << Array1_size << " numbers in file " << infile << " is:\n"; 
    for (int i = 0; i < Array1_size; i++) {
        cout << Array1[i] << endl;
    }
    cout << endl;

    // Inputting second file
    cout << "Enter the second input file name: ";
    cin >> infile;
    instream.open((char*)infile.c_str());

    // Error handling
    if (instream.fail()) {
        cout << "Input file opening failed.\n";
        return 0;
    }

    // Using readfile function to find array 2 size
    Array2_size = readfile(Array2, instream);

    // Closing the second file stream
    instream.close();

    // Outputting numbers
    cout << "The list of " << Array2_size << " numbers in file " << infile << " is:\n"; 
    for (int i = 0; i < Array2_size; i++) {
        cout << Array2[i] << endl;
    }
    cout << endl;

    // Using sortfile to find output array size
    outputArray_size = sort(Array1, Array1_size, Array2, Array2_size, outputArray);

    // Outputting sorted list
    cout << "The sorted list of " << outputArray_size << " numbers is: ";
    for(int i = 0; i < outputArray_size; i++) {
        cout << outputArray[i] << " ";
    }
    cout << endl;

    // Writing to another file
    cout << "Enter the output file name: ";
    cin >> outfile;
    writefile(outputArray, outputArray_size, outfile);
    cout << "*** Please check the new file - " << outfile << " ***\n";
    cout << "*** Goodbye. ***";

    return 0;
}

/**************************************************************************************/
/**************************** Functions  **********************************************/
/**************************************************************************************/
int readfile(int inputArray[], ifstream& instream) {
    // Setting index to zero
    int index = 0;
    
    // Iterating through file
    instream >> inputArray[index];
    while(!instream.eof()) {
        index++;
        instream >> inputArray[index];
    }

    // Returning amount of numbers in file
    return index;
}

int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]) {
    // Setting output array index to zero
    int oaIndex = 0;

    // Adding all numbers from array 1 to output array
    for (int i = 0; i < inputArray1_size; i++) {
        outputArray[oaIndex] = inputArray1[i];
        oaIndex++;
    }

    // Adding all numbers from array 2 to output array
    for (int i = 0; i < inputArray2_size; i++) {
        outputArray[oaIndex] = inputArray2[i];
        oaIndex++;
    }

    // Sorting output array
    sort(outputArray, outputArray + oaIndex);

    // Returning size of output array
    return oaIndex;
    
}

void writefile(int outputArray[], int outputArray_size, string outfile) {
    // Creating out stream
    ofstream outstream;
    outstream.open((char*)outfile.c_str());

    // Error handling
    if (outstream.fail()) {
        cout << "Output file opening failed";
    }

    // Writing to output file
    outstream << "The sorted list of " << outputArray_size << " numbers is: ";
    for(int i = 0; i < outputArray_size; i++) {
        outstream << outputArray[i] << " ";
    }
    
    // Closing the stream
    outstream.close();
}