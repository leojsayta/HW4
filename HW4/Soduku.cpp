//
//  Soduku.cpp
//  HW4
//
//  Created by Joel Atyas on 3/10/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include <boost/numeric/ublas/io.hpp>

#include "Soduku.h"

//using namespace boost::numeric::ublas;
//
//template <typename T>
//Puzzle<T>::Puzzle()
//{
//    this->pGrid = new matrix<T>(this->initDimenNum, this->initDimenNum);
//    
//    if (initGridValue != NULL)
//    {
//        // Create row and col keys for 9x9 map
//        // Letters for rows and Numbers for cols
//        for (int row = 0; row < this->pGrid->size1(); row++)
//        {
//            for (int col = 0; col < this->pGrid->size2(); col++)
//            {
//                //this->pGrid[this->rowLabels.substr(row,1) + this->colLabels.substr(col,1)] = 0;
//                this->pGrid->insert_element(row, col, initGridValue);
//            }
//        }
//    }
//    
//}
//
//template <typename T>
//Puzzle<T>::Puzzle(T initGridWithVal)
//{
//    this->initGridValue = initGridWithVal;
//    Puzzle<T>();
//}
//
//template <typename T>
//Puzzle<T>::Puzzle(T initGridWithVal, int initGridWithDimen)
//{
//    this->initGridValue = initGridWithVal;
//    this->initDimenNum = initGridWithDimen;
//    
//    Puzzle<T>();
//}
//
//template <typename T>
//Puzzle<T>::~Puzzle()
//{
//    delete this->pGrid;
//}
//
//template <typename T>
//void Puzzle<T>::PrintMatrix(matrix<T>& m)
//{
//    //using namespace boost::numeric::ublas;
//    
//    for (int r = 0; r < m.size1(); r++)
//    {
//        std::cout << matrix_row< matrix<T> >(m, r) << std::endl;
//    }
//}
//
//template <typename T>
//void Puzzle<T>::PrintPuzzle()
//{
//    //using namespace boost::numeric::ublas;
//    
//    for (int r = 0; r < this->getGrid()->size1(); r++)
//    {
//        std::cout << matrix_row< matrix<T> >(*this->getGrid(), r) << std::endl;
//    }
//}
//
//template <typename T>
//void Puzzle<T>::PrintPuzzleRegions()
//{
//    //using namespace boost::numeric::ublas;
//    
//    for (matrix<T> m: *this->GetRegions(3, 3))
//    {
//        Puzzle::PrintMatrix(m);
//        cout << std::endl;
//    }
//}
//
//template <typename T>
//bool Puzzle<T>::SetValue(int row, int col, T val)
//{
//    try
//    {
//        this->getGrid()->insert_element(row, col, val);
//        return true;
//    }
//    catch (exception& ex)
//    {
//        return false;
//    }
//}
//
//template <typename T>
//bool Puzzle<T>::IsValidNumber(int row, int col)
//{
//    T currentVal = this->pGrid->at_element(row, col);
//    
//    if (currentVal == this->initGridValue)
//    {
//        return false;        // empty square
//    }
//    
//    matrix_row< matrix<T> > mRow = this->GetRow(row);
//    matrix_column< matrix<T> > mCol = this->GetCol(col);
//    
//    
//    // more stuff here
//    
//    return false;
//}
//
//template <typename T>
//const std::vector< matrix<T> >* Puzzle<T>::GetRegions(int num_y_regions, int num_x_regions)
//{
//    if (this->regions != nullptr)
//        return this->regions;
//    
//    //using boost::numeric::ublas::range;
//    //using boost::numeric::ublas::matrix;
//    //using boost::numeric::ublas::matrix_range;
//    
//    if (this->pGrid->size1() % num_y_regions || this->pGrid->size2() % num_x_regions)
//        return nullptr;
//    
//    for (int ySplit = 0; ySplit < this->pGrid->size1(); ySplit+=num_y_regions)
//    {
//        for (int xSplit = 0; xSplit < this->pGrid->size2(); xSplit+=num_x_regions)
//        {
//            const matrix_range< const matrix<T> > subMatrix(
//                                                            *this->pGrid,
//                                                            range(ySplit, ySplit + num_y_regions),
//                                                            range(xSplit, xSplit + num_x_regions));
//            this->regions->push_back(matrix<T>(subMatrix));
//        }
//    }
//    
//    return this->regions;
//}