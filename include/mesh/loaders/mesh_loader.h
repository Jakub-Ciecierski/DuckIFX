//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_MESH_LOADER_H
#define DUCK_MESH_LOADER_H

#include "mesh.h"

class MeshLoader {
private:

public:

    MeshLoader();

    ~MeshLoader();

    static Mesh LoadTriangle();
    static Mesh LoadSqaure();
    static Mesh LoadCube();
    static Mesh LoadLamp();

};


#endif //DUCK_MESH_LOADER_H
