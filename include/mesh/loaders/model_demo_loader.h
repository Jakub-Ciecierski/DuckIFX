//
// Created by jakub on 5/28/16.
//

#ifndef DUCK_MODEL_DEMO_LOADER_H
#define DUCK_MODEL_DEMO_LOADER_H

#include <mesh/model.h>

/*
 * Uses ModelLoader to load demo models
 */
class ModelDemoLoader {
private:

public:

    ModelDemoLoader();

    ~ModelDemoLoader();

    static Model LoadNanoSuitModel();
    static Model LoadCubeModel();
    static Model LoadLampModel();
    static Model LoadPlaneModel(int x, int y, float unit);
};


#endif //DUCK_MODEL_DEMO_LOADER_H
