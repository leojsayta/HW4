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
#include <boost/numeric/ublas/matrix.hpp>
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
    matrix<T>* pSolved;
    T initGridValue;
    T incrementValue;
    T maxGridValue;
    int initDimenNum;
    int xDimSize;
    int yDimSize;
    int num_y_regions;
    int num_x_regions;
    
    int numSqrsPerSide;
    int effAxisLgth;
    
    std::vector< matrix<T> >* regions;
    std:: vector<bool> itemSet;
    
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
        return matrix_row< matrix<T> >(this->pOrig, rowNum);
    }
    
    matrix_column< matrix<T> > getCol(int colNum)
    {
        return matrix_column< matrix<T> >(this->pOrig, colNum);
    }
    
    matrix<T> getGrid()
    {
        return this->pOrig;
    }
    
    bool solve(int& rowIndex, int& colIndex);
    
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
    
    
    static int convertItem(const T item);
    
    static T convertInt(const int val);
    
    const T GetValue(int row, int col);
    
    bool SetValue(int row, int col, T val);
    
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
    
    int GetXDimSize() const
    {
        return this->xDimSize;
    }
    
    int GetYDimSize() const
    {
        return this->yDimSize;
    }
    
    int GetNum_Y_Regions() const
    {
        return this->num_y_regions;
    }
    
    int GetNum_X_Regions() const
    {
        return this->num_x_regions;
    }
    
    matrix<T> GetOrigPuzzleGrid() const
    {
        return this->pOrig;
    }
    
    matrix<T> GetSolvedPuzzleGrid() const
    {
        return this->pSolved;
    }
    
    const std::vector< matrix<T> >* GetPuzzleRegions();
    
    const std::vector< matrix<T> >* GetPuzzleRegions(int yNumRegions, int xNumRegions);
    
    bool ContainsMultipleVal(int rowIndex, int colIndex, T val);
    
    bool ContainsMultipleVal(matrix_row< matrix<T> >& mRow, T val);
    
    bool ContainsMultipleVal(matrix_column< matrix<T> >& mRow, T val);
    
    bool ContainsMultipleVal(matrix<T>& m, T val);
    
    bool RegionContainsMultipleVal(int rowIndex, int colIndex, T val);
    
    matrix<T> GetEncapsulatingRegion(int rowIndex, int colIndex);
    
    matrix<T> GetEncapsulatingRegion(matrix<T>& m, int rowIndex, int colIndex);
    
    static int ConvertItemToInt(T item, int (*convertItem)(const T));
    
    static T ConvertIntToItem(int val, T (*convertInt)(const int));
    
    void CreateItemSet(int rowIndex, int colIndex);
    
    bool IsInItemSet(T val);
    
    bool IsValidNumber(int row, int col, T val = T{}, bool createItemSet = false);
    
    void Solve();

    static void PrintMatrix(matrix<T>& m, ostream& out = cout);
    
    void PrintPuzzle(ostream& out = cout);
    
    void PrintPuzzleSolution(ostream& out = cout);
    
    void PrintPuzzleRegions(ostream& out = cout);
    
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
        for (int row = 0; row < this->GetYDimSize(); row++)
        {
            for (int col = 0; col < this->GetXDimSize(); col++)
            {
                this->pOrig->insert_element(row, col, this->initGridValue);
            }
        }
    }
    
    this->pSolved = new matrix<T>(*this->pOrig);
    
    this->itemSet = std::vector<bool>(this->GetMaxGridValue() + 1, false);
    
    this->xDimSize = this->initDimenNum;
    this->yDimSize = this->initDimenNum;
    
    this->numSqrsPerSide = this->num_y_regions;
    this->effAxisLgth = this->numSqrsPerSide - 1;
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
    this->pOrig = matrix<T>((origP.GetOrigPuzzleGrid()));
    this->pSolved = matrix<T>((origP.GetSolvedPuzzleGrid()));
}

template <typename T>
Puzzle<T>::~Puzzle()
{
    delete this->pOrig;
    delete this->pSolved;
    delete this->regions;
}

template <typename T>
const T Puzzle<T>::GetValue(int row, int col)
{
    return this->pOrig->operator()(row, col);
}

template <typename T>
bool Puzzle<T>::SetValue(int row, int col, T val)
{
    try
    {
        this->pOrig->insert_element(row, col, val);
        this->pSolved->insert_element(row, col, val);
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
bool Puzzle<T>::RegionContainsMultipleVal(int rowIndex, int colIndex, T val)
{
    using boost::numeric::ublas::range;
    using boost::numeric::ublas::matrix;
    using boost::numeric::ublas::matrix_range;
    
    int yRemDwn = this->effAxisLgth - rowIndex%this->numSqrsPerSide;
    int yRemUp = rowIndex%this->numSqrsPerSide;
    int xRemRt = this->effAxisLgth - colIndex%this->numSqrsPerSide;
    int xRemLft = colIndex%this->numSqrsPerSide;
    
    int rowStart = rowIndex - yRemUp;
    int rowEnd = rowIndex + yRemDwn + 1;
    
    int colStart = colIndex - xRemLft;
    int colEnd = colIndex + xRemRt + 1;
    
    int count = 0;
    for (int row = rowStart; row < rowEnd; row++)
    {
        for (int col = colStart; col < colEnd; col++)
        {
            if (val == this->pSolved(row, col))
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
    int yRemDwn = this->effAxisLgth - rowIndex%this->numSqrsPerSide;
    int yRemUp = rowIndex%this->numSqrsPerSide;
    int xRemRt = this->effAxisLgth - colIndex%this->numSqrsPerSide;
    int xRemLft = colIndex%this->numSqrsPerSide;
    
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
    if (this->regions != NULL)
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
    
    if (this->GetYDimSize() % num_y_regions || this->GetXDimSize() % num_x_regions)
        return nullptr;
    
    int rowStart = 0;
    int rowEnd = 0;
    int colStart = 0;
    int colEnd = 0;
    
    for (int ySplit = 0; ySplit < this->GetYDimSize(); ySplit+=num_y_regions)
    {
        for (int xSplit = 0; xSplit < this->GetXDimSize(); xSplit+=num_x_regions)
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
int Puzzle<T>::ConvertItemToInt(T item, int (*convertItem)(const T))
{
    return convertItem(item);
}

template <typename T>
T Puzzle<T>::ConvertIntToItem(int val, T (*convertInt)(const int))
{
    return convertInt(val);
}

template <typename T>
void Puzzle<T>::CreateItemSet(int rowIndex, int colIndex)
{
    using boost::numeric::ublas::range;
    using boost::numeric::ublas::matrix;
    using boost::numeric::ublas::matrix_range;
    
    for (int b = 1; b < this->itemSet.size(); b++)
        this->itemSet[b] = false;
    
    T item = T{};
    for (int col = 0; col < this->GetXDimSize(); col++)
    {
        if (colIndex != col)
        {
            item = (*this->pSolved)(rowIndex, col);
            this->itemSet[this->convertItem(item)] = true;
        }
    }
    
    for (int row = 0; row < this->GetYDimSize(); row++)
    {
        if (rowIndex != row)
        {
            item = (*this->pSolved)(row, colIndex);
            this->itemSet[this->convertItem(item)] = true;
        }
    }
    
    int yRemDwn = this->effAxisLgth - rowIndex%this->numSqrsPerSide;
    int yRemUp = rowIndex%this->numSqrsPerSide;
    int xRemRt = this->effAxisLgth - colIndex%this->numSqrsPerSide;
    int xRemLft = colIndex%this->numSqrsPerSide;
    
    int rowStart = rowIndex - yRemUp;
    int rowEnd = rowIndex + yRemDwn + 1;
    
    int colStart = colIndex - xRemLft;
    int colEnd = colIndex + xRemRt + 1;
    
    for (int row = rowStart; row < rowEnd; row++)
    {
        for (int col = colStart; col < colEnd; col++)
        {
            if (row != rowIndex && col != colIndex)
            {
                item = (*this->pSolved)(row, col);
                this->itemSet[this->convertItem(item)] = true;
            }
        }
    }
}

template <typename T>
bool Puzzle<T>::IsInItemSet(T val)
{
    return this->itemSet[this->convertItem(val)];
}

template <typename T>
bool Puzzle<T>::IsValidNumber(int rowIndex, int colIndex, T val, bool createItemSet)
{
    if (val == this->initGridValue)
        return false;        // empty square
    
    if (createItemSet)
        this->CreateItemSet(rowIndex, colIndex);
    
    return !(this->IsInItemSet(val));
}

template <typename T>
bool Puzzle<T>::solve(int& rowIndex, int& colIndex)
{
    bool skipValidCheck = false;
    bool isValidNum = false;
    T val = this->GetInitGridValue();
    
    if ((*this->pOrig)(rowIndex, colIndex) != this->GetInitGridValue())
    {
        skipValidCheck = true;
        isValidNum = true;
    }
    else
    {
        val = (*this->pSolved)(rowIndex, colIndex);
        if (val == this->GetInitGridValue()) {
            val = val + this->GetIncrementValue();
        }
        
        this->CreateItemSet(rowIndex, colIndex);
        
        for (int b = Puzzle::convertItem(val); b < this->itemSet.size(); b++)
        {
            if (!this->itemSet[b])
            {
                val = Puzzle::convertItem(b);
                isValidNum = true;
                break;
            }
        }
    }
    
    if (skipValidCheck || isValidNum)
    {
        if (!skipValidCheck)
            (*this->pSolved)(rowIndex, colIndex) = val;
        
        if (rowIndex == 8)
        {
            if (colIndex == 8)
            {
//                cout << "Solved --" << std::endl;
                return true;
            }
        }
        
        if (colIndex < this->GetXDimSize() - 1)
        {
//            cout << "At row = " << rowIndex << ", col = ++" << colIndex << ", val = " << val << std::endl;
//            cout << std::endl;
//            Puzzle<T>::PrintMatrix(this->pSolved);
//            cout << std::endl;
            
            return solve(rowIndex, ++colIndex);
        }
        else if (rowIndex < this->GetYDimSize() - 1)
        {
//            cout << "At row = ++" << rowIndex << ", col = (-->0)" << colIndex << ", val = " << val << std::endl;
//            cout << std::endl;
//            Puzzle<T>::PrintMatrix(this->pSolved);
//            cout << std::endl;
            colIndex = 0;
            return solve(++rowIndex, colIndex);
        }
    }
    else
    {
        (*this->pSolved)(rowIndex, colIndex) = this->GetInitGridValue();
        return false;
    }
    
    return true;
}

template <typename T>
void Puzzle<T>::Solve()
{
    bool skipValidCheck = false;
    bool isMaxValue = false;
    T val = this->GetInitGridValue();
    int rowIndex = 0;
    int colIndex = 0;
    
    while (!this->solve(rowIndex, colIndex))
    {
        do
        {
            if (colIndex == 0)
            {
                
                if (rowIndex == 0)
                {
                    cout << "Unsolvable by this algorithm:" << std::endl;
                    return;
                }
                
                --rowIndex;
                colIndex = (int)(this->GetXDimSize());
            }
            --colIndex;
            
            skipValidCheck  = ((*this->pOrig)(rowIndex, colIndex) != this->GetInitGridValue());
            isMaxValue = ((*this->pSolved)(rowIndex, colIndex) == this->GetMaxGridValue());
            
            if (!skipValidCheck && isMaxValue)
            {
                (*this->pSolved)(rowIndex, colIndex) = this->GetInitGridValue();
            }
        }
        while ( skipValidCheck || isMaxValue );
        
        val = (*this->pSolved)(rowIndex, colIndex) + this->GetIncrementValue();
        
        (*this->pSolved)(rowIndex, colIndex) = val;
    }
}

template <typename T>
int Puzzle<T>::convertItem(const T item)
{
    return int{item};
}

template <typename T>
T Puzzle<T>::convertInt(const int val)
{
    return T{val};
}

template <typename T>
void Puzzle<T>::PrintMatrix(matrix<T>& m, ostream& out)
{
    for (int r = 0; r < m.size1(); r++)
    {
        out << matrix_row< matrix<T> >(m, r) << std::endl;
    }
}

template <typename T>
void Puzzle<T>::PrintPuzzle(ostream& out)
{
    for (int r = 0; r < this->GetYDimSize(); r++)
    {
        matrix_row< matrix<T> > mRow(*this->pOrig, r);
        out << mRow << std::endl;
    }
}

template <typename T>
void Puzzle<T>::PrintPuzzleSolution(ostream& out)
{
    for (int r = 0; r < this->GetYDimSize(); r++)
    {
        out << matrix_row< matrix<T> >(*this->pSolved, r) << std::endl;
    }
}

template <typename T>
void Puzzle<T>::PrintPuzzleRegions(ostream& out)
{
    for (matrix<T> m: *this->GetPuzzleRegions())
    {
        Puzzle::PrintMatrix(m);
        out << std::endl;
    }
}



#endif /* defined(__HW4__Soduku__) */
