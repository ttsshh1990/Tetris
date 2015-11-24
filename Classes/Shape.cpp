//
//  Shape.cpp
//  Tetris
//
//  Created by tian on 9/24/15.
//
//

#include "Shape.hpp"

USING_NS_CC;

void Shape::spin()
{
    state++;
    if(state == 4) state = 0;
    setBlock();

}

void Shape::rollBack()
{
    state--;
    if (state == -1) {
        state = 3;
    }
    setBlock();
}

bool Shape::init()
{
    if(!Sprite::init()){
        return  false;
    }
    positions = (Vec2*) malloc(sizeof(Vec2) * 16);
    blockSize = BOARD_WIDTH/COL;
    return true;
}

void Shape::initBlock()
{
    state = 0;
    if(fileName.empty()) return;
    for(int i = 0; i < 4; i++){
        auto block = Block::createBlock(fileName);
        this->addChild(block);
        blocks.push_back(block);
    }
}

void Shape::setBlock()
{
    for (int i = 0; i < 4; i++) {
        auto block = blocks.at(i);
        auto position = positions[i*4 + state];
        block->setPosition(position*blockSize);
    }
}

Vec2 Shape::getOriginPoint()
{
    return origin;
}

std::vector<Block*> Shape::getBlocks()
{
    return blocks;
}
