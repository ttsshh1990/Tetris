//
//  Stick.cpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#include "Stick.hpp"
USING_NS_CC;

Stick* Stick::createStick()
{
    auto s = Stick::create();
    s->initBlock();
    return s;
}



void Stick::initBlock()
{
    fileName = "glass_pink.png";
    //b1
    positions[0] = Vec2(0,2);
    positions[1] = Vec2(2,3);
    positions[2] = Vec2(3,1);
    positions[3] = Vec2(1,0);
    //b2
    positions[4] = Vec2(1,2);
    positions[5] = Vec2(2,2);
    positions[6] = Vec2(2,1);
    positions[7] = Vec2(1,1);
    
    //b3
    positions[8] = Vec2(2,2);
    positions[9] = Vec2(2,1);
    positions[10] = Vec2(1,1);
    positions[11] = Vec2(1,2);
    
    //b4
    positions[12] = Vec2(3,2);
    positions[13] = Vec2(2,0);
    positions[14] = Vec2(0,1);
    positions[15] = Vec2(1,3);

    origin = Vec2(1,2);
    Shape::initBlock();
    Shape::setBlock();
}