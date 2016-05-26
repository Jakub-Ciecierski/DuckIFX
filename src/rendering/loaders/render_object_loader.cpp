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

