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

// tokenize string s according to delimiter c
std::vector<string>* split(const string& s, char c);

void getPuzzleData(ifstream& in, Puzzle* pData);

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
        
        Puzzle* sodukuPuzzle;
        
        while (!in.eof())
        {
            sodukuPuzzle = new Puzzle();
            
            getPuzzleData(in, sodukuPuzzle);
            
            const std::vector< matrix<int> >* v = sodukuPuzzle->GetRegions(3, 3);
            
            Puzzle::PrintGrid(*sodukuPuzzle->GetGrid());
            
            cout << std::endl;
        
            for (matrix<int> m: *v)
            {
                Puzzle::PrintGrid(m);
                cout << std::endl;
            }
            
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

void getPuzzleData(ifstream& in, Puzzle* pData)
{
    if (!in)
        throw EXIT_FAILURE;
    
    string strInput;        // string that will contain a lineinput from file
    
    getline(in, strInput, '\n'); // Grab the next line
    
    if (strInput.find("Grid") != strInput.npos)                     // necessary for first Grid... statement
        getline(in, strInput, '\n');
    
    int col = 0;
    int row = 0;

    //iterator<string> iter;
    do
    {
        for (auto sqrPtr = strInput.begin(); sqrPtr != strInput.end(); sqrPtr++, col++)
        {
            char sqrCharVal = (char)(*sqrPtr);
            int sqrNumVal = atoi(&sqrCharVal);
            (pData->GetGrid())->insert_element(col, row, sqrNumVal);
        }
        
        col = 0;
        row++;
        
        getline(in, strInput, '\n');        // Grab the next line
        
    } while ( !in.eof() && (strInput.find("Grid") == strInput.npos) );
}

string convertRowNumToLetter(int row)
{
    switch (row)
    {
        case 0:
            return "A";
            break;
        case 1:
            return "B";
            break;
        case 2:
            return "C";
            break;
        case 3:
            return "D";
            break;
        case 4:
            return "E";
            break;
        case 5:
            return "F";
            break;
        case 6:
            return "G";
            break;
        case 7:
            return "H";
            break;
        case 8:
            return "I";
            break;
        default:
            return EMPTY_STRING;
            break;
    }
    
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

