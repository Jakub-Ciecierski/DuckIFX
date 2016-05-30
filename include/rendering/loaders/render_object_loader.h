//
// Created by jakub on 5/26/16.
//

#ifndef DUCK_RENDER_OBJECT_LOADER_H
#define DUCK_RENDER_OBJECT_LOADER_H


#include <mesh/loaders/mesh_loader.h>
#include <render_object.h>
#include <mesh/model.h>

/*
 * Loads meshes using MeshLoader and creates render objects.
 * Must be created after rendering context is ready.
 */
class RenderObjectLoader {
private:

    Model* nanosuitModel;
    Model* cubeModel;
    Model* lampModel;
    Model* plane;

    void initModels();

public:

    RenderObjectLoader();

    ~RenderObjectLoader();

    RenderObject* loadCubeObject();
    RenderObject* loadLampObject();
    RenderObject* loadnanosuitObject();
    RenderObject* loadPlane(int x, int y, float unit);
};


#endif //DUCK_RENDER_OBJECT_LOADER_H
