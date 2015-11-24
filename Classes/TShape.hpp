//
//  TShape.hpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#ifndef TShape_hpp
#define TShape_hpp

#include <stdio.h>
#include "Shape.hpp"

class TShape:public Shape::Shape
{
public:
    static TShape* createTShape();

    CREATE_FUNC(TShape);
protected:
    void initBlock();
};
#endif /* TShape_hpp */
