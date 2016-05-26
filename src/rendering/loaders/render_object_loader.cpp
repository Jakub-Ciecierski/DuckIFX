//
// Created by jakub on 5/26/16.
//

#include "render_object_loader.h"

RenderObjectLoader::RenderObjectLoader(){
    initMeshes();
}

RenderObjectLoader::~RenderObjectLoader() {

}

void RenderObjectLoader::initMeshes() {
    sqaureMesh = meshLoader.LoadSqaure();
    triangleMesh = meshLoader.LoadTriangle();
    cubeMesh = meshLoader.LoadCube();
}


RenderObject* RenderObjectLoader::loadSqaureObject() {
    RenderObject* renderObject =
            new RenderObject(ObjectID(0), "Sqaure", &sqaureMesh);

    return renderObject;
}

RenderObject* RenderObjectLoader::loadTriangleObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Triangle", &triangleMesh);

    return renderObject;
}

RenderObject *RenderObjectLoader::loadCubeObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Cube", &cubeMesh);

    return renderObject;
}
