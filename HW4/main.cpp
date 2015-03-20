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

typedef boost::numeric::ublas::matrix<int> m_t;


//#define READ_FROM_ARG           // if this is defined read input file from command line"

#define INPUT_FILE_NAME "../../../../../p096_sudoku.txt"
#define OUTPUT_FILE_NAME "../../../../../Answer.txt"

#define COL_WIDTH 15            // set general column width for table
#define COL_MONTH_WIDTH 10      // set month column width

string ROW_LABELS = "ABCDEFGHI";
string COL_LABELS = "123456789";

// tokenize string s according to delimiter c
std::vector<string>* split(const string& s, char c);

template <typename T>
void getPuzzleData(ifstream& in, Puzzle<T>* pData, T (*convert)(char));

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
            sodukuPuzzle = new Puzzle<int>();
            
            //getPuzzleData(in, sodukuPuzzle, atoi);
            
            const std::vector< matrix<int> >* v = sodukuPuzzle->GetRegions(3, 3);

            sodukuPuzzle->PrintPuzzle();

            cout << std::endl;
            
            sodukuPuzzle->PrintPuzzleRegions();
        
            cout << std::endl;
            
            sodukuPuzzle->Insert_Value(0, 1, 20);
            
            sodukuPuzzle->PrintPuzzleRegions();
            
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

bool blah1(matrix<int>& m, m_t::iterator1& itrRow, m_t::iterator2& itrCol)
{
    bool validNumber = true;
    
    int val = *itrRow;
    
    if (validNumber)
    {
        if (itrCol != m.end2())
            blah1(m, itrRow, ++itrCol);
        else if (itrRow != m.end1())
            blah1(m, ++itrRow, itrCol);
        else
            return true;
    }
    else
    {
        if (val == 9)
        {
            return false;
        }
        else
        {
            (*itrRow)++;
            blah1(m, itrRow, itrCol);
        }
    }
    
    return true;
}


bool blah(matrix<int>& m, m_t::iterator1& itrRow, m_t::iterator2& itrCol, int val)
{
    bool validNumber = true;
    
    if (validNumber)
    {
        if (itrRow != m.end1())
        {
            itrRow++;
        }
    }
    else
    {
        if (val == 9)
        {
            
        }
        else
        {
            blah(m, itrRow, itrCol, val + 1);
        }
    }
    
    return true;
}

template <typename T>
void getPuzzleData(ifstream& in, Puzzle<T>* pData, T (*convert)(char))
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
            pData->Insert_Value(col, row, sqrVal);
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

// based on: https://www.safaribooksonline.com/library/view/C+++Cookbook/0596007612/ch04s07.html
std::vector<string>* split(const string& s, char c)
{
    std::vector<string>* v = new std::vector<string>();
    string::size_type i = 0;
    string::size_type j = s.find(c);    // find next location of delimiter c
    
    while (j != string::npos)           // continue processing s until c is not found
    {
        v->push_back(s.substr(i, j - i));   // add substring delimited by c to vector v
        do
        {
            i = ++j;
            j = s.find(c, j);           // find next location of delimiter c
        }
        while (j == i);                 // bypass duplicate delimiters
        
        if (j == string::npos)          // if reached last delimiter in s, add any substring following the last delimiter to v
            v->push_back( s.substr(i, s.length()));
    }
    
    return v;
}

