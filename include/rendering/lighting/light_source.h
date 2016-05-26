//
// Created by jakub on 5/26/16.
//

#ifndef DUCK_LIGHT_SOURCE_H
#define DUCK_LIGHT_SOURCE_H

#include <render_object.h>

/*
 * Light source. Can be rendered if mesh was provided.
 */
class LightSource {
private:
    RenderObject *renderObject;

    glm::vec3 position;
    glm::vec3 lightColor;

    // If true the position will be taken from renderObject if possible.
    bool followObject;

public:

    LightSource();
    LightSource(RenderObject *renderObject);

    ~LightSource();

    void setFollowObject(bool value);

    void setColor(const glm::vec3& color);
    void setPosition(const glm::vec3& position);
    const glm::vec3& getPosition();

    void use(const Program& program);
    void render(const Program& program);
};


#endif //DUCK_LIGHT_SOURCE_H
