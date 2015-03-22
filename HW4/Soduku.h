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
#include <boost/utility/value_init.hpp>


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
    
    matrix<T>* pGrid;
    T initGridValue;
    int initDimenNum;
    int num_y_regions;
    int num_x_regions;
    
    std::vector< matrix<T> >* regions;
    
    matrix<T>* getGrid()
    {
        return this->pGrid;
    }
    
public:
    
    Puzzle(T initGridWithVal = T{}, int initGridWithDimen = 9, int yNumRegions = 3, int xNumRegions = 3);
    
    Puzzle(Puzzle<T> const &);
    
    ~Puzzle();
    
    
    
    
    typename matrix<T>::iterator1 GetRowIter()
    {
        return this->pGrid->begin1();
    }

    typename matrix<T>::iterator2 GetColIter()
    {
        return this->pGrid->begin2();
    }
    
    matrix_row< matrix<T> > GetRow(int rowNum)
    {
        return matrix_row< matrix<T> >(*this->pGrid, rowNum);
    }
    
    matrix_column< matrix<T> > GetCol(int colNum)
    {
        return matrix_column< matrix<T> >(*this->pGrid, colNum);
    }
    
    const T GetValue(int row, int col);
    
    bool SetValue(int row, int col, T val);
    
    const std::vector< matrix<T> >* GetRegions();
    
    const std::vector< matrix<T> >* GetRegions(int yNumRegions, int xNumRegions);
    
    T GetInitGridValue() const
    {
        return this->initGridValue;
    }
    
    int GetDimensionNum() const
    {
        return this->initDimenNum;
    }
    
    int GetNum_Y_Regions() const
    {
        return this->num_y_regions;
    }
    
    int GetNum_X_Regions() const
    {
        return this->num_x_regions;
    }
    
    matrix<T>* GetPuzzleGrid() const
    {
        return this->pGrid;
    }
    
    bool IsValidNumber(int row, int col);

    static void PrintMatrix(matrix<T>& m);
    
    void PrintPuzzle();
    
    void PrintPuzzleRegions();
    
};

template <typename T>
Puzzle<T>::Puzzle(T initGridWithVal, int initGridWithDimen, int yNumRegions, int xNumRegions):
    initGridValue(initGridWithVal),
    initDimenNum(initGridWithDimen),
    num_y_regions(yNumRegions),
    num_x_regions(xNumRegions)
{
    this->pGrid = new matrix<T>(this->initDimenNum, this->initDimenNum);
    
    if (initGridValue != T{})
    {
        for (int row = 0; row < this->pGrid->size1(); row++)
        {
            for (int col = 0; col < this->pGrid->size2(); col++)
            {
                this->pGrid->insert_element(row, col, initGridValue);
            }
        }
    }
}

template <typename T>
Puzzle<T>::Puzzle(Puzzle<T> const & origP):
    Puzzle<T>(T{}, origP.GetDimensionNum(), origP.GetNum_Y_Regions(), origP.GetNum_X_Regions())
{
    this->initGridValue = origP.GetInitGridValue();
    this->pGrid = new matrix<T>(*(origP.GetPuzzleGrid()));
}

template <typename T>
Puzzle<T>::~Puzzle()
{
    delete this->pGrid;
}

template <typename T>
const T Puzzle<T>::GetValue(int row, int col)
{
    return this->getGrid()->operator()(row, col);
}

template <typename T>
bool Puzzle<T>::SetValue(int row, int col, T val)
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
const std::vector< matrix<T> >* Puzzle<T>::GetRegions()
{
    if (this->regions != nullptr)
        return this->regions;
    else
        return this->GetRegions(this->num_y_regions, this->num_x_regions);
}

template <typename T>
const std::vector< matrix<T> >* Puzzle<T>::GetRegions(int yNumRegions, int xNumRegions)
{
    if (this->num_y_regions == yNumRegions
        && this->num_x_regions == xNumRegions
        && this->regions != nullptr)
        return this->regions;
    
    this->num_y_regions = yNumRegions;
    this->num_x_regions = xNumRegions;
    
    //using boost::numeric::ublas::range;
    //using boost::numeric::ublas::matrix;
    //using boost::numeric::ublas::matrix_range;
    
    if (this->pGrid->size1() % num_y_regions || this->pGrid->size2() % num_x_regions)
        return nullptr;
    
    for (int ySplit = 0; ySplit < this->pGrid->size1(); ySplit+=num_y_regions)
    {
        for (int xSplit = 0; xSplit < this->pGrid->size2(); xSplit+=num_x_regions)
        {
            const matrix_range< const matrix<T> > subMatrix(
                                                            *this->pGrid,
                                                            range(ySplit, ySplit + num_y_regions),
                                                            range(xSplit, xSplit + num_x_regions));
            this->regions->push_back(matrix<T>(subMatrix));
        }
    }
    
    return this->regions;
}

template <typename T>
bool Puzzle<T>::IsValidNumber(int row, int col)
{
    T currentVal = this->pGrid->at_element(row, col);
    
    if (currentVal == this->initGridValue)
    {
        return false;        // empty square
    }
    
    matrix_row< matrix<T> > mRow = this->GetRow(row);
    matrix_column< matrix<T> > mCol = this->GetCol(col);
    const std::vector< matrix<int> >* v = this->GetRegions(3, 3);
    
    // more stuff here
    
    return false;
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
    
    for (matrix<T> m: *this->GetRegions())
    {
        Puzzle::PrintMatrix(m);
        cout << std::endl;
    }
}



#endif /* defined(__HW4__Soduku__) */
