//
//  SShape.hpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#ifndef SShape_hpp
#define SShape_hpp

#include <stdio.h>
#include "Shape.hpp"

class SShape : public Shape::Shape
{
public:
    static SShape* createSShape();
    CREATE_FUNC(SShape);
protected:
    void initBlock();
};


#endif /* SShape_hpp */
