//
//  Soduku.h
//  HW4
//
//  Created by Joel Atyas on 3/10/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#ifndef __HW4__Soduku__
#define __HW4__Soduku__

#include <iomanip>
#include <algorithm>
#include <string>
#include <exception>
#include <map>
#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>


using namespace std;
using namespace boost::numeric::ublas;

class Sequence
{
private:
    
    
public:
    
};

class Puzzle
{
private:
    
    matrix<int>* sGrid;
    int initGridValue = 0;
    int initDimenNum = 9;
    
    //map<string,int> sGrid;
    
    string rowLabels = "ABCDEFGHI";
    string colLabels = "123456789";
    
    void createGrid();
    
    
public:
    
    Puzzle();
    
    Puzzle(int initGridVal);
    
    Puzzle(int initGridVal, int initDimenNum);
    
    ~Puzzle();
    
    matrix<int>* GetGrid()
    {
        return this->sGrid;
    }
    
    static void PrintGrid(matrix<int> m);
    
    boost::numeric::ublas::matrix<int>::iterator1 GetRowIter()
    {
        return this->sGrid->begin1();
    }

    boost::numeric::ublas::matrix<int>::iterator2 GetColIter()
    {
        return this->sGrid->begin2();
    }
    
    boost::numeric::ublas::matrix_row< matrix<int> > GetRow(int rowNum)
    {
        return matrix_row< matrix<int> >(*this->sGrid, rowNum);
    }
    
    
    boost::numeric::ublas::matrix_column< matrix<int> > GetCol(int colNum)
    {
        return matrix_column< matrix<int> >(*this->sGrid, colNum);
    }
    
    const std::vector< boost::numeric::ublas::matrix<int> >* GetRegions(int num_y_regions, int num_x_regions);
    
    
    bool IsValidNumber(int row, int col);
    
};

#endif /* defined(__HW4__Soduku__) */
