//
//  main.cpp
//  Exam 4
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
#include <ctime>

using namespace std;

#define READ_FROM_ARG           // if this is defined read input file from command line, else get file from "../../../../../hotel.txt"

#define COL_WIDTH 15            // set general column width for table
#define COL_MONTH_WIDTH 10      // set month column width

// process input file data, put data in pData vector
void processRevenueData(string& inputFileName, vector< vector<double>* >* pData);

// create formatted revenue report from pData and output to file named outputFileName
void createRevenueReport(string& outputFileName, const vector< vector<double>* >* const pData);

// tokenize string s according to delimiter c
vector<string>* split(const string& s, char c);

// convert month integer (0 - 11) to month string name
string getMonthStr(int month);

// created formatted stream for report title using titleStrm
void createTitle(ofstream& outputfile);

// created formatted stream for table header using headerStrm
void createHeader(ofstream& outputfile);

// create formatted table data from pData, and output to file using out
void createRevenueTable(ofstream& outputfile, const vector< vector<double>* >* const pData);

//            if (colIndex == 0)
//            {
//                cout << "At row = --" << rowIndex << ", col = " << colIndex << " (->" << this->pSolved.size2() - 1 << "), val = " << val << " (Max)" << std::endl;
//                cout << std::endl;
//                Puzzle<T>::PrintMatrix(this->pSolved);
//                cout << std::endl;
//
//                this->pSolved(rowIndex, colIndex) = this->GetIncrementValue();
//
//
//                --rowIndex;
//                colIndex = (int)(this->pSolved.size2());
//
//
//                T tmpVal = this->pSolved(rowIndex, --colIndex) + this->GetIncrementValue();
//                bool isValFixed = (this->pOrig->operator()(rowIndex, colIndex) != this->GetInitGridValue());
//                while (isValFixed    // Check for initially set value
//                       ||
//                       tmpVal >= this->GetMaxGridValue())
//                {
//                    if (!isValFixed)
//                        this->pSolved(rowIndex, colIndex) = this->GetIncrementValue();
//
//                    tmpVal = this->pSolved(rowIndex, --colIndex) + this->incrementValue;
//                    isValFixed = (this->pOrig->operator()(rowIndex, colIndex) != this->GetInitGridValue());
//                }
//
//                cout << "At row = " << rowIndex << ", col = " << colIndex << ", val = " << tmpVal << std::endl;
//                cout << std::endl;
//                Puzzle<T>::PrintMatrix(this->pSolved);
//                cout << std::endl;
//
//                this->pSolved(rowIndex, colIndex) = tmpVal;
//
//                solve(rowIndex, colIndex);
//            }
//            else
//            {
//            cout << "At row = " << rowIndex << ", col = --" << colIndex << ", val = " << val << " (Max)" << std::endl;
//            cout << std::endl;
//            Puzzle<T>::PrintMatrix(this->pSolved);
//


int mainsail(int argc, const char *argv[])
{
    try
    {
        //printf("Starting...\n\n");
        
        string inputFileName = "../../../../../hotel.txt";;             // string that contains the name of the file for processing
        string outputFileName = "../../../../../hotelAnswer.txt";       // string that contains the name of the file for report generation
        
#ifdef READ_FROM_ARG
        
        if (argc < 2)
            return (EXIT_FAILURE);
        else
            inputFileName = argv[1];
        
        if (argc > 2)
            outputFileName = argv[2];
#endif
        
        // pData will eventually contain all processed data from input file
        // pData elements represent months of calendar year
        // ex. pData[0] - pData[11] == Jan - Dec
        vector< vector<double>* >* pData = new vector< vector<double>* >(12);
        
        
        // pData sub-vectors contain info for its parent month:
        // pData[x][0] == lodging
        // pData[x][1] == dining
        // pData[x][2] == conferences
        // pData[x][3] == receptions
        // pData[x][4] == spa
        for (int i = 0; i < pData->size(); i++)
        {
            pData->at(i) = new vector<double>(5);       // for each month set appropriate vector size
        }
        
        // process input file data, put data in pData vector
        processRevenueData(inputFileName, pData);
        
        // create revenue report and output to disk
        createRevenueReport(outputFileName, pData);
        
        // clean up references
        for (vector< vector<double>* >::iterator p = pData->begin(); p != pData->end(); ++p)
        {
            delete *p;
        }
        
        //cout << "Ending..." << '\n';
    }
    catch (exception& ex)
    {
        printf("\nSomething went wrong:\n");
        //printf(ex.what());
        printf("\nPlease start over.");
        return 1;
    }
    
    return 0;
}

// based on: https://www.safaribooksonline.com/library/view/C+++Cookbook/0596007612/ch04s07.html
vector<string>* split(const string& s, char c)
{
    vector<string>* v = new vector<string>();
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

void processRevenueData(string& inputFileName, vector< vector<double>* >* pData)
{
    ifstream in(inputFileName);  // open file for processing
    
    if (!in)
        throw EXIT_FAILURE;
    
    string strInput;        // string that will contain a lineinput from file
    
    vector<string>* pSalesEntryTxt = NULL;  // contains parsed line of input
    vector<string>* pDateTxt = NULL;        // contains parsed date
    
    while (!in.eof())       // continue processing data until end of file
    {
        getline(in, strInput, '\n'); // Grab the next line
        
        if (strInput.empty())
            continue;
        
        pSalesEntryTxt = split(strInput, ' ');                      // parse retrieved line of input
        pDateTxt = split(pSalesEntryTxt->operator[](2), '/');       // parse date text
        
        int serviceCode = stoi(pSalesEntryTxt->at(1));              // get revenue service code
        int month = stoi(pDateTxt->at(0));                          // get month of revenue
        double revenue = stod(pSalesEntryTxt->at(3));               // get revenue
        
        pData->at(month - 1)->at(serviceCode) += revenue;           // add revenue to running total for month
        
    }
    
    in.close();         // close file handle
}

string getMonthStr(int month)
{
    switch (month) {
        case 0:
            return "January";
            break;
        case 1:
            return "February";
            break;
        case 2:
            return "March";
            break;
        case 3:
            return "April";
            break;
        case 4:
            return "May";
            break;
        case 5:
            return "June";
            break;
        case 6:
            return "July";
            break;
        case 7:
            return "August";
            break;
        case 8:
            return "September";
            break;
        case 9:
            return "October";
            break;
        case 10:
            return "November";
            break;
        case 11:
            return "December";
            break;
        default:
            break;
    }
    
    return NULL;
}

void createRevenueReport(string& outputFileName, const vector< vector<double>* >* const pData)
{
    // open file for report output
    ofstream out(outputFileName);
    
    if (!out)
        throw EXIT_FAILURE;
    
    // Report Title
    createTitle(out);               // created formatted stream for title
    
    // Table Header
    createHeader(out);              // created formatted stream for table header
    
    // Table Data
    createRevenueTable(out, pData); // create formatted stream for table data
    
    out.close();    // close file handle
    
}

void createTitle(ofstream& outputfile)
{
    string strOutput;               // string that will contain a line of formatted output to be sent to file
    
    ostringstream titleStrm;         // formatted output stream for report title
    titleStrm.setf(ios::left);       // set justification
    
    // get current date/time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    // components of tm structure.
    // cout << "Year: "<< 1900 + ltm->tm_year << endl;
    // cout << "Month: "<< 1 + ltm->tm_mon<< endl;
    // cout << "Day: "<<  ltm->tm_mday << endl;
    // cout << "Time: "<< 1 + ltm->tm_hour << ":";
    // cout << 1 + ltm->tm_min << ":";
    // cout << 1 + ltm->tm_sec << endl;
    
    // Report Title
    titleStrm << "              Hotel 2014 Receipt Totals by Month and Service Type" << endl << endl;
    titleStrm << "              Produced by Joel Atyas" << endl << endl;
    titleStrm << "              Date: " << getMonthStr(1 + ltm->tm_mon) << " " << ltm->tm_mday << ", " << 1900 + ltm->tm_year << endl << endl << endl;
    
    strOutput = titleStrm.str();            // create string from formatted stream for output
    
    outputfile << strOutput;               // send string output to file
    outputfile.flush();
}

void createHeader(ofstream& outputfile)
{
    string strOutput;               // string that will contain a line of formatted output to be sent to file
    ostringstream headerStrm;        // formatted output stream for table header
    
    headerStrm.setf(ios::left);
    headerStrm.width(COL_MONTH_WIDTH);
    headerStrm << "MONTH";
    
    headerStrm.setf(ios::right);
    headerStrm.width(COL_WIDTH);
    headerStrm << "LODGING";
    
    headerStrm.width(COL_WIDTH);
    headerStrm << "DINING";
    
    headerStrm.width(COL_WIDTH);
    headerStrm << "CONFERENCES";
    
    headerStrm.width(COL_WIDTH);
    headerStrm << "RECEPTIONS";
    
    headerStrm.width(COL_WIDTH);
    headerStrm << "SPA";
    
    headerStrm.width(COL_WIDTH);
    headerStrm << "TOTAL";
    
    headerStrm << "\n\n";
    
    strOutput = headerStrm.str();           // create string from formatted stream for output
    
    outputfile << strOutput;                // send output to file
    outputfile.flush();
}

void createRevenueTable(ofstream& outputfile, const vector< vector<double>* >* const pData)
{
    string strOutput;               // string that will contain a line of formatted output to be sent to file
    double totalRevenue = 0.0;      // total revenue for particular month
    
    // Table
    for (int i = 0; i < pData->size(); i++)
    {
        totalRevenue = 0.0;
        ostringstream revenueStrm;       // formatted output stream for table row
        
        revenueStrm.setf(ios::left);
        revenueStrm.setf(ios::fixed);
        revenueStrm.precision(2);
        
        revenueStrm.width(COL_MONTH_WIDTH);
        revenueStrm << getMonthStr(i);                      // convert month integer to string
        
        revenueStrm.width(COL_WIDTH);
        revenueStrm.setf(ios::right);
        for (int j = 0; j < pData->at(i)->size(); j++)      // create formatted table entries
        {
            totalRevenue+=pData->at(i)->at(j);
            
            revenueStrm.width(COL_WIDTH);
            revenueStrm << pData->at(i)->at(j);
        }
        
        revenueStrm.width(COL_WIDTH);
        revenueStrm << totalRevenue;
        
        revenueStrm << "\n\n";
        
        strOutput = revenueStrm.str();          // create string from formatted stream for output
        
        outputfile << strOutput;               // send output to file
        outputfile.flush();
    }
}

