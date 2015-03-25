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
    
    matrix<T>* pOrig;
    matrix<T> pSolved;
    T initGridValue;
    T incrementValue;
    T maxGridValue;
    int initDimenNum;
    int num_y_regions;
    int num_x_regions;
    
    std::vector< matrix<T> >* regions;
    
    typename matrix<T>::iterator1 getRowIter()
    {
        return this->pOrig->begin1();
    }
    
    typename matrix<T>::iterator2 getColIter()
    {
        return this->pOrig->begin2();
    }
    
    matrix_row< matrix<T> > getRow(int rowNum)
    {
        return matrix_row< matrix<T> >(*this->pOrig, rowNum);
    }
    
    matrix_column< matrix<T> > getCol(int colNum)
    {
        return matrix_column< matrix<T> >(*this->pOrig, colNum);
    }
    
    matrix<T>* getGrid()
    {
        return this->pOrig;
    }

    void solve(int rowIndex, int colIndex);
    
public:
    
    Puzzle(
           T initGridWithVal = T{},
           T incrementVal = T{},
           T maxGridVal = T{},
           int initGridWithDimen = 9,
           int yNumRegions = 3,
           int xNumRegions = 3);
    
    Puzzle(Puzzle<T> const &);
    
    ~Puzzle();
    
    
    const T GetValue(int row, int col);
    
    bool SetValue(int row, int col, T val);
    
    bool ContainsMultipleVal(matrix_row< matrix<T> >& mRow, T val);
    
    bool ContainsMultipleVal(matrix_column< matrix<T> >& mRow, T val);
    
    bool ContainsMultipleVal(matrix<T>& m, T val);
    
    matrix<T> GetEncapsulatingRegion(int rowIndex, int colIndex);
    
    matrix<T> GetEncapsulatingRegion(matrix<T>& m, int rowIndex, int colIndex);
    
    const std::vector< matrix<T> >* GetPuzzleRegions();
    
    const std::vector< matrix<T> >* GetPuzzleRegions(int yNumRegions, int xNumRegions);
    
    T GetInitGridValue() const
    {
        return this->initGridValue;
    }
    
    T GetIncrementValue() const
    {
        return this->incrementValue;
    }
    
    T GetMaxGridValue() const
    {
        return this->maxGridValue;
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
    
    matrix<T>* GetOrigPuzzleGrid() const
    {
        return this->pOrig;
    }
    
    matrix<T>* GetSolvedPuzzleGrid() const
    {
        return this->pSolved;
    }
    
    bool IsValidNumber(int row, int col, T val = T{});
    
    void Solve();

    static void PrintMatrix(matrix<T>& m);
    
    void PrintPuzzle();
    
    void PrintPuzzleSolution();
    
    void PrintPuzzleRegions();
    
};

template <typename T>
Puzzle<T>::Puzzle(
                  T initGridWithVal,
                  T incrementVal,
                  T maxGridVal,
                  int initGridWithDimen,
                  int yNumRegions,
                  int xNumRegions):
    initGridValue(initGridWithVal),
    incrementValue(incrementVal),
    maxGridValue(maxGridVal),
    initDimenNum(initGridWithDimen),
    num_y_regions(yNumRegions),
    num_x_regions(xNumRegions)

{
    this->pOrig = new matrix<T>(this->initDimenNum, this->initDimenNum);
    
    if (this->initGridValue != T{})
    {
        for (int row = 0; row < this->pOrig->size1(); row++)
        {
            for (int col = 0; col < this->pOrig->size2(); col++)
            {
                this->pOrig->insert_element(row, col, this->initGridValue);
            }
        }
    }
    
    this->pSolved = matrix<T>(*this->pOrig);
}

template <typename T>
Puzzle<T>::Puzzle(Puzzle<T> const & origP):
    Puzzle<T>(
              origP.GetInitGridValue(),
              origP.GetIncrementValue(),
              origP.GetMaxGridValue(),
              origP.GetDimensionNum(),
              origP.GetNum_Y_Regions(),
              origP.GetNum_X_Regions())
{
    this->pOrig = new matrix<T>(*(origP.GetOrigPuzzleGrid()));
    this->pSolved = matrix<T>(*(origP.GetSolvedPuzzleGrid()));
}

template <typename T>
Puzzle<T>::~Puzzle()
{
    delete this->pOrig;
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
        this->pSolved.insert_element(row, col, val);
        return true;
    }
    catch (exception& ex)
    {
        return false;
    }
}

template <typename T>
bool Puzzle<T>::ContainsMultipleVal(matrix_row< matrix<T> >& mRow, T val)
{
    int count = 0;
    for (T item: mRow)
    {
        if (item == val)
            count++;
        if (count > 1)
            return true;
    }
    
    return count > 1 ? true: false;
}

template <typename T>
bool Puzzle<T>::ContainsMultipleVal(matrix_column< matrix<T> >& mCol, T val)
{
    int count = 0;
    for (T item: mCol)
    {
        if (item == val)
            count++;
        if (count > 1)
            return true;
    }
    
    return count > 1 ? true : false;
}

template <typename T>
bool Puzzle<T>::ContainsMultipleVal(matrix<T>& m, T val)
{
    using boost::numeric::ublas::range;
    using boost::numeric::ublas::matrix;
    using boost::numeric::ublas::matrix_range;
    
    int count = 0;
    for (int row = 0; row < m.size1(); row++)
    {
        for (int col = 0; col < m.size2(); col++)
        {
            if (m(row, col) == val)
                count++;
            if (count > 1)
                return true;
        }
    }
    
    return count > 1 ? true : false;
}

template <typename T>
matrix<T> Puzzle<T>::GetEncapsulatingRegion(int rowIndex, int colIndex)
{
    int yRemDwn = 2 - rowIndex%3;
    int yRemUp = rowIndex%3;
    int xRemRt = 2 - colIndex%3;
    int xRemLft = colIndex%3;
    
    int rowStart = rowIndex - yRemUp;
    int rowEnd = rowIndex + yRemDwn + 1;
    
    int colStart = colIndex - xRemLft;
    int colEnd = colIndex + xRemRt + 1;
    
    // Range begin boundary is inclusive
    // Range end boundary is exclusive
    matrix_range< matrix<T> > subMatrix(*this->pOrig, range(rowStart, rowEnd), range(colStart, colEnd));
    return matrix<T>(subMatrix);

}

template <typename T>
matrix<T> Puzzle<T>::GetEncapsulatingRegion(matrix<T>& m, int rowIndex, int colIndex)
{
    int numSqrsPerSide = this->num_y_regions;
    int effAxisLgth = numSqrsPerSide - 1;
    int yRemDwn = effAxisLgth - rowIndex%numSqrsPerSide;
    int yRemUp = rowIndex%numSqrsPerSide;
    int xRemRt = effAxisLgth - colIndex%numSqrsPerSide;
    int xRemLft = colIndex%numSqrsPerSide;
    
    int rowStart = rowIndex - yRemUp;
    int rowEnd = rowIndex + yRemDwn + 1;
    
    int colStart = colIndex - xRemLft;
    int colEnd = colIndex + xRemRt + 1;
    
    // Range begin boundary is inclusive
    // Range end boundary is exclusive
    matrix_range< matrix<T> > subMatrixRange(m, range(rowStart, rowEnd), range(colStart, colEnd));
    matrix<T> subMatrix = matrix<T>(subMatrixRange);
    
    return subMatrix;
    
}

template <typename T>
const std::vector< matrix<T> >* Puzzle<T>::GetPuzzleRegions()
{
    if (this->regions != nullptr)
        return this->regions;
    else
        return this->GetPuzzleRegions(this->num_y_regions, this->num_x_regions);
}

template <typename T>
const std::vector< matrix<T> >* Puzzle<T>::GetPuzzleRegions(int yNumRegions, int xNumRegions)
{
    if (this->num_y_regions == yNumRegions
        && this->num_x_regions == xNumRegions
        && this->regions != nullptr)
        return this->regions;
    else
        this->regions = new std::vector< matrix<T> >;
    
    this->num_y_regions = yNumRegions;
    this->num_x_regions = xNumRegions;
    
    //using boost::numeric::ublas::range;
    //using boost::numeric::ublas::matrix;
    //using boost::numeric::ublas::matrix_range;
    
    if (this->pOrig->size1() % num_y_regions || this->pOrig->size2() % num_x_regions)
        return nullptr;
    
    int rowStart = 0;
    int rowEnd = 0;
    int colStart = 0;
    int colEnd = 0;
    
    for (int ySplit = 0; ySplit < this->pOrig->size1(); ySplit+=num_y_regions)
    {
        for (int xSplit = 0; xSplit < this->pOrig->size2(); xSplit+=num_x_regions)
        {
            rowStart = ySplit;
            rowEnd = ySplit + num_y_regions;
            
            colStart = xSplit;
            colEnd = xSplit + num_x_regions;
            
            // Range begin boundary is inclusive
            // Range end boundary is exclusive
            const matrix_range< const matrix<T> > subMatrix(
                                                            *this->pOrig,
                                                            range(rowStart, rowEnd),
                                                            range(colStart, colEnd));
            this->regions->push_back(matrix<T>(subMatrix));
        }
    }
    
    return this->regions;
}

template <typename T>
bool Puzzle<T>::IsValidNumber(int row, int col, T val)
{
    using boost::numeric::ublas::range;
    using boost::numeric::ublas::matrix;
    using boost::numeric::ublas::matrix_range;
    
    T currentVal;
    if (val != T{})
        currentVal = val;
    else
        currentVal = this->pSolved(row, col);
    
    if (currentVal == this->initGridValue)
    {
        return false;        // empty square
    }
    
    matrix_row< matrix<T> > mRow = matrix_row< matrix<T> >(this->pSolved, row);;
    matrix_column< matrix<T> > mCol = matrix_column< matrix<T> >(this->pSolved, col);;
    matrix<T> subM = this->GetEncapsulatingRegion(this->pSolved, row, col);

    if (this->ContainsMultipleVal(mRow, currentVal))
        return false;
    if (this->ContainsMultipleVal(mCol, currentVal))
        return false;
    if (this->ContainsMultipleVal(subM, currentVal))
        return false;
    
    return true;
}

template <typename T>
void Puzzle<T>::solve(int rowIndex, int colIndex)
{
//    cout << "Starting:  At row = " << rowIndex << ", col = " << colIndex << std::endl;
//    cout << std::endl;
//    Puzzle<T>::PrintMatrix(this->pSolved);
//    cout << std::endl;
    
    bool skipValidCheck = false;
    bool isValidNum = false;
    
    if (this->pOrig->operator()(rowIndex, colIndex) != this->GetInitGridValue())
    {
        skipValidCheck = true;
        isValidNum = true;
    }
    
    T val = this->pSolved(rowIndex, colIndex);
    
    while (!skipValidCheck && !(isValidNum = this->IsValidNumber(rowIndex, colIndex, val)))
    {
        if (val == this->GetMaxGridValue())
            break;
        
        val = val + this->GetIncrementValue();
        this->pSolved(rowIndex, colIndex) = val;
    }
    
    if (skipValidCheck || isValidNum)
    {
        if (colIndex < this->pSolved.size2() - 1)
        {
//            cout << "At row = " << rowIndex << ", col = ++" << colIndex << ", val = " << val << std::endl;
//            cout << std::endl;
//            Puzzle<T>::PrintMatrix(this->pSolved);
//            cout << std::endl;
            
            solve(rowIndex, ++colIndex);
        }
        else if (rowIndex < this->pSolved.size1() - 1)
        {
//            cout << "At row = ++" << rowIndex << ", col = (-->0)" << colIndex << ", val = " << val << std::endl;
//            cout << std::endl;
//            Puzzle<T>::PrintMatrix(this->pSolved);
//            cout << std::endl;
            
            solve(++rowIndex, 0);
        }
    }
    else
    {
        this->pSolved(rowIndex, colIndex) = this->GetInitGridValue();
        bool isMaxValue = false;
        do
        {
            if (colIndex == 0)
            {
                if (rowIndex == 0)
                {
                    cout << "Unsolvable by this algorithm:" << std::endl;
                    cout << "At row = " << rowIndex << ", col = " << colIndex << std::endl;
                    cout << std::endl;
                    Puzzle<T>::PrintMatrix(this->pSolved);
                    cout << std::endl;
                    return;
                }
                
                --rowIndex;
                colIndex = (int)(this->pSolved.size2());
            }
            
            skipValidCheck  = (this->pOrig->operator()(rowIndex, --colIndex) != this->GetInitGridValue());
            isMaxValue = ((val = this->pSolved(rowIndex, colIndex)) == this->GetMaxGridValue());
            
            if (!skipValidCheck && isMaxValue)
            {
                this->pSolved(rowIndex, colIndex) = this->GetInitGridValue();
            }
        }
        while ( skipValidCheck || isMaxValue );
            
        val = val + this->GetIncrementValue();
        
        this->pSolved(rowIndex, colIndex) = val;
        
//        cout << "Reset to row = " << rowIndex << ", col = " << colIndex << ", val = " << val << std::endl;
//        cout << std::endl;
//        Puzzle<T>::PrintMatrix(this->pSolved);
//        cout << std::endl;
        
        solve(rowIndex, colIndex);
    }
    
//    cout << "Original:  " << std::endl;
//    Puzzle<T>::PrintMatrix(*this->pOrig);
//    cout << std::endl;
//    
//    cout << "Solved?:" << std::endl;
//    Puzzle<T>::PrintMatrix(this->pSolved);
//    cout << std::endl;
}

template <typename T>
void Puzzle<T>::Solve()
{
    this->solve(0, 0);
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
void Puzzle<T>::PrintPuzzleSolution()
{
    //using namespace boost::numeric::ublas;
    
    for (int r = 0; r < this->pSolved.size1(); r++)
    {
        std::cout << matrix_row< matrix<T> >(this->pSolved, r) << std::endl;
    }
}

template <typename T>
void Puzzle<T>::PrintPuzzleRegions()
{
    //using namespace boost::numeric::ublas;
    
    for (matrix<T> m: *this->GetPuzzleRegions())
    {
        Puzzle::PrintMatrix(m);
        cout << std::endl;
    }
}



#endif /* defined(__HW4__Soduku__) */
