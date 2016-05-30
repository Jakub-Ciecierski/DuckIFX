//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_MESH_LOADER_H
#define DUCK_MESH_LOADER_H

#include "mesh.h"

/*
 * Loads specific meshes to the system
 */
class MeshLoader {
private:

public:

    MeshLoader();

    ~MeshLoader();

    static Mesh LoadCube();
    static Mesh LoadLamp();
    static Mesh LoadPlane(int x, int y, float unit);

};


#endif //DUCK_MESH_LOADER_H
