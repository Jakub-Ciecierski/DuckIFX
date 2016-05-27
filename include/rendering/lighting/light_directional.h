//
// Created by jakub on 5/27/16.
//

#ifndef DUCK_LIGHT_DIRECTIONAL_H
#define DUCK_LIGHT_DIRECTIONAL_H


#include "light_source.h"

/*
 * Directional Light has a lookAt position which is used
 * to compute a direction.
 *
 * It binds the direction with the shader
 */
class LightDirectional : public LightSource{
private:
    // Defines the direction of the light.
    // Will be used if light is not set on follow with camera
    glm::vec3 lookAt;

protected:
    virtual void bind(const Program& program) override;

public:

    LightDirectional();

    LightDirectional(RenderObject* object);

    ~LightDirectional();

    /*
     * Gets direction either from the camera or based on its own
     * position and lookAt
     */
    const glm::vec3 getDirection();

    void setLookAt(const glm::vec3& lookAt);
};


#endif //DUCK_LIGHT_DIRECTIONAL_H
