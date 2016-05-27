//
// Created by jakub on 5/27/16.
//

#ifndef DUCK_LIGHT_GLOBAL_H
#define DUCK_LIGHT_GLOBAL_H


#include "light_source.h"

/*
 * Global Light simply binds the position with the shader.
 */
class LightGlobal : public LightSource{
protected:
    virtual void bind(const Program& program) override ;

public:

    LightGlobal();

    LightGlobal(RenderObject *renderObject);

    ~LightGlobal();



};


#endif //DUCK_LIGHT_GLOBAL_H
