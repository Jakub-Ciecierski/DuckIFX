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

    objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
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

    objectColor = other.objectColor;

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

void Mesh::bindColor(const Program& program){
    // Color
    GLint objectColorLoc = glGetUniformLocation(program.getID(),
                                                OBJECT_COLOR_NAME.c_str());
    glUniform3f(objectColorLoc, objectColor.x, objectColor.y, objectColor.z);
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