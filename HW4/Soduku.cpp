//
//  Soduku.cpp
//  HW4
//
//  Created by Joel Atyas on 3/10/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include "Soduku.h"


Puzzle::Puzzle()
{
    
//    for (pair<const string,int>& item: this->sGrid)
//    {
//        
//    }
    
    sGrid = new matrix<int,column_major>(9,9);
    
    // Create row and col keys for 9x9 map
    // Letters for rows and Numbers for cols
    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {
            //this->sGrid[this->rowLabels.substr(row,1) + this->colLabels.substr(col,1)] = 0;
            this->sGrid->insert_element(col, row, 0);
        }
    }
    
}