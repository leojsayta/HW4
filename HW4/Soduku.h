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

template <typename T>
class Puzzle
{
private:
    
    matrix<T>* sGrid;
    T initGridValue = NULL;
    int initDimenNum = 9;
    
    std::vector< matrix<T> >* regions = nullptr;
    
    //map<string,T> sGrid;
    
    //string rowLabels = "ABCDEFGHI";
    //string colLabels = "123456789";
    
    void createGrid();
    
    matrix<T>* getGrid()
    {
        return this->sGrid;
    }
    
public:
    
    Puzzle();
    
    Puzzle(T initGridVal);
    
    Puzzle(T initGridVal, int initDimenNum);
    
    ~Puzzle();
    
    static void PrintMatrix(matrix<T>& m);
    
    void PrintPuzzle();
    
    void PrintPuzzleRegions();
    
    bool Insert_Value(int row, int col, T val);
    
    typename matrix<T>::iterator1 GetRowIter()
    {
        return this->sGrid->begin1();
    }

    typename matrix<T>::iterator2 GetColIter()
    {
        return this->sGrid->begin2();
    }
    
    matrix_row< matrix<T> > GetRow(int rowNum)
    {
        return matrix_row< matrix<T> >(*this->sGrid, rowNum);
    }
    
    
    matrix_column< matrix<T> > GetCol(int colNum)
    {
        return matrix_column< matrix<T> >(*this->sGrid, colNum);
    }
    
    const std::vector< matrix<T> >* GetRegions(int num_y_regions, int num_x_regions);
    
    
    bool IsValidNumber(int row, int col);
    
};

template <typename T>
Puzzle<T>::Puzzle()
{
    this->sGrid = new matrix<T>(this->initDimenNum, this->initDimenNum);
    
    if (initGridValue != NULL)
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

template <typename T>
Puzzle<T>::Puzzle(T initGridWithVal)
{
    this->initGridValue = initGridWithVal;
    Puzzle<T>();
}

template <typename T>
Puzzle<T>::Puzzle(T initGridWithVal, int initGridWithDimen)
{
    this->initGridValue = initGridWithVal;
    this->initDimenNum = initGridWithDimen;
    
    Puzzle<T>();
}

template <typename T>
Puzzle<T>::~Puzzle()
{
    delete this->sGrid;
}

template <typename T>
void Puzzle<T>::PrintMatrix(matrix<T>& m)
{
    //using namespace boost::numeric::ublas;
    
    for (int r = 0; r < m.size1(); r++)
    {
        std::cout << matrix_row< matrix<T> >(m, r) << std::endl;
    }
}

template <typename T>
void Puzzle<T>::PrintPuzzle()
{
    //using namespace boost::numeric::ublas;
    
    for (int r = 0; r < this->getGrid()->size1(); r++)
    {
        std::cout << matrix_row< matrix<T> >(*this->getGrid(), r) << std::endl;
    }
}

template <typename T>
void Puzzle<T>::PrintPuzzleRegions()
{
    //using namespace boost::numeric::ublas;
    
    for (matrix<T> m: *this->GetRegions(3, 3))
    {
        Puzzle::PrintMatrix(m);
        cout << std::endl;
    }
}

template <typename T>
bool Puzzle<T>::Insert_Value(int row, int col, T val)
{
    try
    {
        this->getGrid()->insert_element(row, col, val);
        return true;
    }
    catch (exception& ex)
    {
        return false;
    }
}

template <typename T>
bool Puzzle<T>::IsValidNumber(int row, int col)
{
    T currentVal = this->sGrid->at_element(row, col);
    
    if (currentVal == this->initGridValue)
    {
        return false;        // empty square
    }
    
    matrix_row< matrix<T> > mRow = this->GetRow(row);
    matrix_column< matrix<T> > mCol = this->GetCol(col);
    
    
    // more stuff here
    
    return false;
}

template <typename T>
const std::vector< matrix<T> >* Puzzle<T>::GetRegions(int num_y_regions, int num_x_regions)
{
    if (this->regions != nullptr)
        return this->regions;
    
    //using boost::numeric::ublas::range;
    //using boost::numeric::ublas::matrix;
    //using boost::numeric::ublas::matrix_range;
    
    if (this->sGrid->size1() % num_y_regions || this->sGrid->size2() % num_x_regions)
        return nullptr;
    
    for (int ySplit = 0; ySplit < this->sGrid->size1(); ySplit+=num_y_regions)
    {
        for (int xSplit = 0; xSplit < this->sGrid->size2(); xSplit+=num_x_regions)
        {
            const matrix_range< const matrix<T> > subMatrix(
                                                            *this->sGrid,
                                                            range(ySplit, ySplit + num_y_regions),
                                                            range(xSplit, xSplit + num_x_regions));
            this->regions->push_back(matrix<T>(subMatrix));
        }
    }
    
    return this->regions;
}

#endif /* defined(__HW4__Soduku__) */
