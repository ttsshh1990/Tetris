//
//  MathMethod.cpp
//  Tetris
//
//  Created by tian on 10/6/15.
//
//

#include "MathMethod.hpp"

int MathMethod::ceil(float t)
{
    int t_int = (int) t;
    if( (t - t_int) == 0.0 ) return t_int;
    else return t_int + 1;
}

int MathMethod::floor(float t)
{
    return (int) t;
}

int MathMethod::round(float t)
{
    return (int) (t+0.5);
}