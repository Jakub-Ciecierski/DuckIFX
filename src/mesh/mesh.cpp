//
// Created by jakub on 5/24/16.
//

#include <iostream>
#include <stdexcept>
#include "mesh.h"


using namespace std;

Mesh::Mesh(){

}

Mesh::Mesh(std::vector<Vertex> vertices,
           vector <GLuint>& indices,
           GLenum drawingMode) :
        vertices(vertices), indices(indices){
    this->drawingMode = drawingMode;
    checkError();
    initBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertices,
           vector <GLuint>& indices,
           vector<Texture>& textures,
           GLenum drawingMode) :
        vertices(vertices), indices(indices), textures(textures){
    this->drawingMode = drawingMode;
    checkError();
    initBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertices,
           vector <GLuint>& indices,
           vector<Texture>& textures,
           Material material,
           GLenum drawingMode) :
        vertices(vertices), indices(indices), textures(textures),
        material(material){
    this->drawingMode = drawingMode;
    checkError();
    initBuffers();
}
Mesh::Mesh(const Mesh& mesh){
    copy(mesh);
}

Mesh::~Mesh() {
    delete vao;

    delete vbo;
    delete ebo;
}

void Mesh::checkError(){
    int textureCount = textures.size();

    if(textureCount > MAX_TEX_COUNT){
        throw std::invalid_argument("Too many textures");
    }
}

void Mesh::copy(const Mesh& other){
    vertices = other.vertices;
    indices = other.indices;
    textures = other.textures;
    material = other.material;
    drawingMode = other.drawingMode;
    initBuffers();
}

void Mesh::initBuffers(){
    vao = new VAO();

    vbo = new VBO(&vertices);
    ebo = new EBO(&indices);

    vao->bindBuffers(*vbo, *ebo);
}

void Mesh::bindTextures(const Program& program){
    for(unsigned int i = 0; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(textures[i].type, textures[i].id);
        if(textures[i].texType == TextureTypes::DIFFUSE){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             MATERIAL_DIFFUSE_NAME.c_str()),i);
        }else if(textures[i].texType == TextureTypes::SPECULAR){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             MATERIAL_SPECULAR_NAME.c_str()),i);
        }else{
            // TODO check proper naming convetion
            glUniform1i(glGetUniformLocation(program.getID(),
                                             TEX_UNI_NAMES[i].c_str()), i);
        }
    }
}

void Mesh::bindColor(const Program& program){
    GLint matShineLoc = glGetUniformLocation(program.getID(),
                                             MATERIAL_SHININESS_NAME.c_str());

    glUniform1f(matShineLoc, material.shininess);
}

void Mesh::setMaterial(const Material& material){
    this->material = material;
}

void Mesh::draw(const Program& program){
    program.use();

    this->bindTextures(program);
    this->bindColor(program);

    vao->bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao->unbind();
}

Mesh& Mesh::operator=(const Mesh& other){
    copy(other);

    return *this;
}

std::string Mesh::toString() const{
    string str = "";
    int diffuseTexCount = 0;
    int specularTexCount = 0;
    for(unsigned int i = 0; i < textures.size(); i++){
        if(textures[i].texType == TextureTypes::DIFFUSE)
            diffuseTexCount++;
        if(textures[i].texType == TextureTypes::SPECULAR)
            specularTexCount++;
    }

    str += "Vertices Count:          " + to_string(vertices.size()) + "\n";
    str += "Texture Diffuse Count:   " + to_string(diffuseTexCount) + "\n";
    str += "Texture Specular Count:  " + to_string(specularTexCount) + "\n";

    return str;
}

std::vector<Vertex> Mesh::getVertices() {
    return vertices;
}