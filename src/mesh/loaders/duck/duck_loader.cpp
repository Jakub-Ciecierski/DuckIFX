//
// Created by jakub on 5/30/16.
//

#include "duck_loader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <textures/texture_loader.h>

using namespace std;
using namespace glm;

DuckLoader::DuckLoader(){

}

DuckLoader::~DuckLoader() {

}

std::vector<std::string> DuckLoader::splitString(std::string s,
                                                 std::string delimiter) {
    std::vector<std::string> tokens;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

Model DuckLoader::loadDuckModel() {
    vector<Vertex> vertices;
    vector<GLuint> indices;

    string filepath = "res/models/duck/duck.txt";
    ifstream fileStream(filepath);
    if(!fileStream){
        throw new invalid_argument("No such duck file");
    }
    string line;
    getline(fileStream, line);

    int vertexCount = stoi(line);
    for(int i = 0; i < vertexCount; i++){
        getline(fileStream, line);
        vector<string> vertexStr = splitString(line, " ");
        if(vertexStr.size() != 8){
            throw new invalid_argument("No such duck file");

        }
        vec3 pos = vec3(atof(vertexStr[0].c_str()),
                        atof(vertexStr[1].c_str()),
                        atof(vertexStr[2].c_str()));
        vec3 norm = vec3(atof(vertexStr[3].c_str()),
                         atof(vertexStr[4].c_str()),
                         atof(vertexStr[5].c_str()));
        vec2 tex = vec2(atof(vertexStr[6].c_str()),
                         atof(vertexStr[7].c_str()));

        Vertex vertex;
        vertex.Position = pos;
        vertex.Normal = norm;
        vertex.TexCoords = tex;
        vertices.push_back(vertex);
    }

    getline(fileStream, line);
    int indexCount = stoi(line);
    for(int i = 0; i < indexCount; i++){
        getline(fileStream, line);
        vector<string> indexStr = splitString(line, " ");

        GLuint i1 = stoi(indexStr[0]);
        GLuint i2 = stoi(indexStr[1]);
        GLuint i3 = stoi(indexStr[2]);
        indices.push_back(i1);
        indices.push_back(i2);
        indices.push_back(i3);
    }

    TextureLoader textureLoader;
    string texturePath = "res/models/duck/ducktex.jpg";
    Texture texture = textureLoader.loadTexture(texturePath,
                                                TextureTypes::DIFFUSE);
    Texture textureSpec = textureLoader.loadTexture(texturePath,
                                                    TextureTypes::SPECULAR);

    vector<Texture> textures = {texture, textureSpec};
    Material material;
    material.shininess = 32.0f;
    Mesh mesh(vertices, indices, textures);
    mesh.setMaterial(material);

    vector<Mesh> meshes = {mesh};
    Model model (meshes);

    return model;
}
