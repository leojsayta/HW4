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
#include <boost/numeric/ublas/vector.hpp>


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
    
    matrix<int,column_major>* sGrid;
    
    //map<string,int> sGrid;
    
    string rowLabels = "ABCDEFGHI";
    string colLabels = "123456789";
    
    void createGrid();
    
    
public:
    
    matrix<int,column_major>* GetGrid()
    {
        return this->sGrid;
    }

    Puzzle();
};

#endif /* defined(__HW4__Soduku__) */
