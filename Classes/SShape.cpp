//
//  SShape.cpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#include "SShape.hpp"

USING_NS_CC;

SShape* SShape::createSShape()
{
    auto s = SShape::create();
    
    s->initBlock();
    
    return s;
}

void SShape::initBlock()
{
    fileName = "glass_green.png";
    //b1
    positions[0] = Vec2(0,1);
    positions[1] = Vec2(1,2);
    positions[2] = Vec2(0,0);
    positions[3] = Vec2(0,2);
    //b2
    positions[4] = Vec2(1,1);
    positions[5] = Vec2(1,1);
    positions[6] = Vec2(1,0);
    positions[7] = Vec2(0,1);
    
    //b3
    positions[8] = Vec2(1,2);
    positions[9] = Vec2(2,1);
    positions[10] = Vec2(1,1);
    positions[11] = Vec2(1,1);
    
    //b4
    positions[12] = Vec2(2,2);
    positions[13] = Vec2(2,0);
    positions[14] = Vec2(2,1);
    positions[15] = Vec2(1,0);
    
   
    origin = Vec2(1, 1);
    Shape::initBlock();
    Shape::setBlock();
}