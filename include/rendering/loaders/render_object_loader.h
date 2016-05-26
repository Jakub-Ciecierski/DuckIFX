//
// Created by jakub on 5/26/16.
//

#ifndef DUCK_RENDER_OBJECT_LOADER_H
#define DUCK_RENDER_OBJECT_LOADER_H


#include <mesh/loaders/mesh_loader.h>
#include <render_object.h>

/*
 * Loads meshes using MeshLoader and creates render objects
 */
class RenderObjectLoader {
private:
    MeshLoader meshLoader;

    Mesh sqaureMesh;
    Mesh triangleMesh;
    Mesh cubeMesh;

    void initMeshes();

public:

    RenderObjectLoader();

    ~RenderObjectLoader();

    RenderObject* loadSqaureObject();
    RenderObject* loadTriangleObject();
    RenderObject* loadCubeObject();
};


#endif //DUCK_RENDER_OBJECT_LOADER_H
