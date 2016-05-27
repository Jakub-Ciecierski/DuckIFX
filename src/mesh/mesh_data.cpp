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

const std::string VIEW_POSITION_NAME = "viewPos";

const std::string MATERIAL_DIFFUSE_NAME = "material.diffuse";
const std::string MATERIAL_SPECULAR_NAME = "material.specular";
const std::string MATERIAL_SHININESS_NAME = "material.shininess";

const std::string LIGHT_POSITION_NAME = "light.position";
const std::string LIGHT_DIRECTION_NAME = "light.direction";
const std::string LIGHT_AMBIENT_NAME = "light.ambient";
const std::string LIGHT_DIFFUSE_NAME = "light.diffuse";
const std::string LIGHT_SPECULAR_NAME = "light.specular";

const std::string LIGHT_ATTENUATION_CONST_NAME = "light.constant";
const std::string LIGHT_ATTENUATION_LINEAR_NAME = "light.linear";
const std::string LIGHT_ATTENUATION_QUAD_NAME = "light.quadratic";

const std::string LIGHT_FLASHLIGHT_CUTOFF_NAME = "light.cutOff";
const std::string LIGHT_FLASHLIGHT_OUTER_CUTOFF_NAME = "light.outerCutOff";