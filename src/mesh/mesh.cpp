//
// Created by jakub on 5/24/16.
//

#include <iostream>
#include <stdexcept>
#include "mesh.h"


using namespace std;

Mesh::Mesh(){

}

Mesh::Mesh(vector <GLfloat>& vertices,
           vector <GLuint>& indices) :
    vertices(vertices), indices(indices){
    checkError();
    initBuffers();
}

Mesh::Mesh(vector<GLfloat>& vertices,
           vector <GLuint>& indices,
           vector<Texture>& textures) :
        vertices(vertices), indices(indices), textures(textures){
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
        glUniform1i(glGetUniformLocation(program.getID(),
                                         TEX_UNI_NAMES[i].c_str()), i);
    }
}

const std::vector<GLfloat> Mesh::getVertices() const{
    return this->vertices;
}

void Mesh::draw(const Program& program){
    program.use();
    this->bindTextures(program);

    vao->bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao->unbind();
}

Mesh& Mesh::operator=(const Mesh& other){
    copy(other);

    return *this;
}