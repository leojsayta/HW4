//
//  main.cpp
//  HW4
//
//  Created by Joel Atyas on 2/22/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include <map>
#include <utility>
#include <cctype>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/detail/iterator.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "Soduku.h"

using namespace std;
using namespace boost::numeric::ublas;

#define EMPTY_STRING ""

//#define READ_FROM_ARG           // if this is defined read input file from command line"

#define INPUT_FILE_NAME "../../../../../p096_sudoku.txt"
#define OUTPUT_FILE_NAME "../../../../../Answer.txt"

#define COL_WIDTH 15            // set general column width for table
#define COL_MONTH_WIDTH 10      // set month column width

string ROW_LABELS = "ABCDEFGHI";
string COL_LABELS = "123456789";

string convertRowNumToLetter(int row);
string convertColNumToLetter(int col);

template <typename T, typename Q>
void getPuzzleData(ifstream& in, Puzzle<T>* pData, T (*convert)(const Q*));

int main(int argc, const char *argv[])
{
    try
    {
        //printf("Starting...\n\n");
        
        string inputFileName = INPUT_FILE_NAME;     // string that contains the name of the input file for processing
        string outputFileName = OUTPUT_FILE_NAME;   // string that contains the name of the file for output generation
        
#ifdef READ_FROM_ARG
        
        if (argc < 2)
            return (EXIT_FAILURE);
        else
            inputFileName = argv[1];
        
        if (argc > 2)
            outputFileName = argv[2];
#endif
        // open file for processing
        ifstream in(inputFileName);
        
        if (!in)
            return (EXIT_FAILURE);
        
        Puzzle<int>* sodukuPuzzle;
        
        while (!in.eof())
        {
            sodukuPuzzle = new Puzzle<int>(0,1,9);
            
            getPuzzleData<int, char>(in, sodukuPuzzle, atoi);
            sodukuPuzzle->PrintPuzzle();
            cout << std::endl;
            
//            sodukuPuzzle->GetPuzzleRegions();
//            sodukuPuzzle->PrintPuzzleRegions();
//            cout << std::endl;
            
//            matrix<int> subM = sodukuPuzzle->GetEncapsulatingRegion(0, 1);
//            Puzzle<int>::PrintMatrix(subM);
//            cout << std::endl;
            
//            sodukuPuzzle->SetValue(0, 1, 20);
//            int tmp = sodukuPuzzle->GetValue(0, 1);
//            sodukuPuzzle->PrintPuzzle();
//            cout << std::endl;
            
//            Puzzle<int> tp(*sodukuPuzzle);
//            tp.PrintPuzzle();
//            cout << std::endl;
            
//            matrix<int> subM = sodukuPuzzle->GetEncapsulatingRegion(5, 6);
//            Puzzle<int>::PrintMatrix(subM);
//            cout << std::endl;
            
//            sodukuPuzzle->PrintPuzzleRegions();
//            cout << std::endl;
            
            sodukuPuzzle->Solve();
            sodukuPuzzle->PrintPuzzleSolution();
            cout << std::endl;
            
            delete sodukuPuzzle;
        }
        

        in.close();         // close file handle
        
        
        //cout << "Ending..." << '\n';
    }
    catch (exception& ex)
    {
        return 1;
    }
    
    return 0;
}

template <typename T, typename Q>
void getPuzzleData(ifstream& in, Puzzle<T>* pData, T (*convert)(const Q*))
{
    if (!in)
        throw EXIT_FAILURE;
    
    string strInput;                                // string that will contain a lineinput from file
    
    getline(in, strInput, '\n');                    // Grab the next line
    
    if (strInput.find("Grid") != strInput.npos)     // necessary for first Grid... statement
        getline(in, strInput, '\n');
    
    int col = 0;
    int row = 0;

    do
    {
        for (auto sqrPtr = strInput.begin(); sqrPtr != strInput.end(); sqrPtr++, col++)
        {
            char sqrCharVal = (char)(*sqrPtr);
            T sqrVal = convert(&sqrCharVal);
            //T sqrVal = atoi(&sqrCharVal);
            pData->SetValue(row, col, sqrVal);
        }
        
        col = 0;
        row++;
        
        getline(in, strInput, '\n');                // Grab the next line
        
    } while ( !in.eof() && (strInput.find("Grid") == strInput.npos) );
}

string convertRowNumToLetter(int row)
{
    return &ROW_LABELS[row];
    
    return EMPTY_STRING;
}

string convertColNumToLetter(int col)
{
    return &COL_LABELS[col];
    
    return EMPTY_STRING;
}
