//
//  Block.cpp
//  Tetris
//
//  Created by tian on 9/24/15.
//
//

#include "Block.hpp"
#include "GameParameter.h"

USING_NS_CC;
Block* Block::createBlock(const std::string picName)
{
    auto block = Block::create();
    block->initWithFile(picName);
    int blockSize = BOARD_WIDTH/COL;
    block->setBlockSize(blockSize);
    Size size = block->getContentSize();
    block->setScale(blockSize/size.width);
    block->setAnchorPoint(Vec2(0,0));
    return block;
}

int Block::getBlockSize()
{
    return blockSize;
}

void Block::setBlockSize(int s)
{
    blockSize = s;
}