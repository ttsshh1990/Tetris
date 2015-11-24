//
//  ZShape.hpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#ifndef ZShape_hpp
#define ZShape_hpp

#include <stdio.h>
#include "Shape.hpp"

class ZShape : public Shape::Shape
{
public:
    static ZShape* createZShape();

    CREATE_FUNC(ZShape);
protected:
    void initBlock();
};

#endif /* ZShape_hpp */
