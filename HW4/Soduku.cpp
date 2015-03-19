//
//  Soduku.cpp
//  HW4
//
//  Created by Joel Atyas on 3/10/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include <boost/numeric/ublas/io.hpp>

#include "Soduku.h"


Puzzle::Puzzle()
{
    
//    for (pair<const string,int>& item: this->sGrid)
//    {
//        
//    }
    
    this->sGrid = new matrix<int>(this->initDimenNum, this->initDimenNum);
    
    if (initGridValue != 0)
    {
        // Create row and col keys for 9x9 map
        // Letters for rows and Numbers for cols
        for (int row = 0; row < this->sGrid->size1(); row++)
        {
            for (int col = 0; col < this->sGrid->size2(); col++)
            {
                //this->sGrid[this->rowLabels.substr(row,1) + this->colLabels.substr(col,1)] = 0;
                this->sGrid->insert_element(row, col, initGridValue);
            }
        }
    }
    
}

Puzzle::Puzzle(int initGridWithVal)
{
    this->initGridValue = initGridWithVal;
    Puzzle();
}

Puzzle::Puzzle(int initGridWithVal, int initGridWithDimen)
{
    this->initGridValue = initGridWithVal;
    this->initDimenNum = initGridWithDimen;
    
    Puzzle();
}

Puzzle::~Puzzle()
{
    delete this->sGrid;
}

void Puzzle::PrintGrid(matrix<int> m)
{
    using namespace boost::numeric::ublas;
    
    for (int r = 0; r < m.size1(); r++)
    {
        std::cout << matrix_row< matrix<int> >(m, r) << std::endl;
    }
    
    
}

bool Puzzle::IsValidNumber(int row, int col)
{
    int currentVal = this->sGrid->at_element(row, col);
    
    if (currentVal == this->initGridValue)
    {
        return false;        // empty square
    }
    
    boost::numeric::ublas::matrix_row< matrix<int> > mRow = this->GetRow(row);
    boost::numeric::ublas::matrix_column< matrix<int> > mCol = this->GetCol(col);
    
    
    
    return false;
}

const std::vector< boost::numeric::ublas::matrix<int> >* Puzzle::GetRegions(int num_y_regions, int num_x_regions)
{
    using boost::numeric::ublas::range;
    using boost::numeric::ublas::matrix;
    using boost::numeric::ublas::matrix_range;
    
    matrix<int>* m = this->sGrid;
    
//    const uint64_t y = m->size1() / num_y_regions;
//    const uint64_t x = m->size2() / num_x_regions;
    
    if (m->size1() % num_y_regions || m->size2() % num_x_regions)
        return nullptr;
    
    
    std::vector< matrix<int> >* v = new std::vector< matrix<int> >();
    

    for (int ySplit = 0; ySplit < m->size1(); ySplit+=num_y_regions)
    {
        for (int xSplit = 0; xSplit < m->size2(); xSplit+=num_x_regions)
        {
            const matrix_range< const matrix<int> > subMatrix(
                                                            *m,
                                                            range(ySplit, ySplit + num_y_regions),
                                                            range(xSplit, xSplit + num_x_regions));
            v->push_back(matrix<int>(subMatrix));
        }
    }
    
    return v;
}