//
//  Square.hpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#ifndef Square_hpp
#define Square_hpp

#include <stdio.h>
#include "Shape.hpp"

class Square : public Shape::Shape
{
public:
    static Square* createSquare();
    void spin();
    void rollBack();
    CREATE_FUNC(Square);
protected:
    void initBlock();
    
};

#endif /* Square_hpp */
