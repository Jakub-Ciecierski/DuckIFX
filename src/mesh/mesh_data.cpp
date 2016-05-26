//
// Created by jakub on 5/24/16.
//

#include "mesh_data.h"

// Maximum number of textures
const int MAX_TEX_COUNT = 16;

/*
 * This names must correspond to texture samplers names in fragment shader
 */
const std::string TEX_UNI_NAMES[MAX_TEX_COUNT] = {
        "tex1", "tex2", "tex3", "tex4",
        "tex5", "tex6", "tex7", "tex8",
        "tex9", "tex10", "tex11", "tex12",
        "tex13", "tex14", "tex15", "tex16",
};

const std::string MODEL_MATRIX_NAME = "ModelMatrix";
const std::string VIEW_MATRIX_NAME = "ViewMatrix";
const std::string PROJECTION_MATRIX_NAME = "ProjectionMatrix";