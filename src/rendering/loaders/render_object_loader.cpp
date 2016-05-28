//
// Created by jakub on 5/26/16.
//

#include <mesh/loaders/model_demo_loader.h>
#include "render_object_loader.h"

RenderObjectLoader::RenderObjectLoader(){
    initModels();
}

RenderObjectLoader::~RenderObjectLoader() {
    delete nanosuitModel;
    delete cubeModel;
    delete lampModel;
}

void RenderObjectLoader::initModels() {
    nanosuitModel = new Model(ModelDemoLoader::LoadNanoSuitModel());
    cubeModel = new Model(ModelDemoLoader::LoadCubeModel());
    lampModel = new Model(ModelDemoLoader::LoadLampModel());
}

RenderObject *RenderObjectLoader::loadCubeObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Cube", cubeModel);

    return renderObject;
}

RenderObject *RenderObjectLoader::loadLampObject() {
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "Lamp", lampModel);

    return renderObject;
}

RenderObject* RenderObjectLoader::loadnanosuitObject(){
    RenderObject* renderObject
            = new RenderObject(ObjectID(0), "NanoSuit", nanosuitModel);

    return renderObject;
}