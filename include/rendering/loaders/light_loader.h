//
// Created by jakub on 5/27/16.
//

#ifndef DUCK_LIGHT_LOADER_H
#define DUCK_LIGHT_LOADER_H


#include <lighting/light_global.h>
#include <lighting/light_directional.h>

/*
 * Loads specific lights to the system
 */
class LightLoader {
private:

public:

    LightLoader();

    ~LightLoader();

    LightGlobal* loadLightGlobal();
    LightDirectional* loadLightDirectional();
};


#endif //DUCK_LIGHT_LOADER_H
