//
//  Square.cpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#include "Square.hpp"
USING_NS_CC;

Square* Square::createSquare()
{
    Square* square = Square::create();
    square->initBlock();
    return square;
}

void Square::spin()
{
    
}

void Square::rollBack()
{
    
}

void Square::initBlock()
{
    fileName = "glass_yellow.png";
    //b1
    positions[0] = Vec2(0,0);
    positions[1] = Vec2(2,3);
    positions[2] = Vec2(3,1);
    positions[3] = Vec2(1,0);
    //b2
    positions[4] = Vec2(0,1);
    positions[5] = Vec2(2,3);
    positions[6] = Vec2(2,3);
    positions[7] = Vec2(2,3);
    
    //b3
    positions[8] = Vec2(1,0);
    positions[9] = Vec2(2,3);
    positions[10] = Vec2(2,3);
    positions[11] = Vec2(2,3);
    
    //b4
    positions[12] = Vec2(1,1);
    positions[13] = Vec2(2,3);
    positions[14] = Vec2(2,3);
    positions[15] = Vec2(2,3);
    

    origin = Vec2(0, 0);
    Shape::initBlock();
    Shape::setBlock();
}