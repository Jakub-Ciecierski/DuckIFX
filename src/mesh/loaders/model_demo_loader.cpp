//
// Created by jakub on 5/28/16.
//

#include <mesh/loaders/model_loader.h>
#include <mesh/loaders/mesh_loader.h>
#include <mesh/loaders/duck/duck_loader.h>
#include "model_demo_loader.h"

ModelDemoLoader::ModelDemoLoader(){

}

ModelDemoLoader::~ModelDemoLoader() {

}

Model ModelDemoLoader::LoadNanoSuitModel() {
    std::string path = "res/models/nanosuit/nanosuit.obj";

    ModelLoader loader(path);

    return loader.loadModel();
}

Model ModelDemoLoader::LoadCubeModel() {
    MeshLoader meshLoader;
    Mesh mesh = meshLoader.LoadCube();
    std::vector<Mesh> meshes = {mesh};

    return Model(meshes);
}

Model ModelDemoLoader::LoadCubemapModel(){
    MeshLoader meshLoader;
    Mesh mesh = meshLoader.LoadCubemap();
    std::vector<Mesh> meshes = {mesh};

    return Model(meshes);
}

Model ModelDemoLoader::LoadLampModel() {
    MeshLoader meshLoader;
    Mesh mesh = meshLoader.LoadLamp();
    std::vector<Mesh> meshes = {mesh};

    return Model(meshes);
}

Model ModelDemoLoader::LoadPlaneModel(int x, int y, float unit) {
    MeshLoader meshLoader;
    Mesh mesh = meshLoader.LoadPlane(x, y, unit);
    std::vector<Mesh> meshes = {mesh};

    return Model(meshes);
}

Model ModelDemoLoader::LoadDuckModel(){
    DuckLoader duckLoader;

    return duckLoader.loadDuckModel();
}