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
#include <vector>
#include <map>

using namespace std;


class Sequence
{
private:
    
    
public:
    
};

class Puzzle
{
private:
    
    map<string,int> sodukoGrid;
    
    string rowLabels = "ABCDEFGHI";
    string colLabels = "123456789";
    
    void createGrid();
    
    
public:
    
    Puzzle();
};

#endif /* defined(__HW4__Soduku__) */
