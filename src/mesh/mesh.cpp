//
// Created by jakub on 5/24/16.
//

#include <iostream>
#include "mesh.h"

using namespace std;

Mesh::Mesh(){

}

Mesh::Mesh(vector <GLfloat>& vertices,
           vector <GLuint>& indices) :
    vertices(vertices), indices(indices){
    initBuffers();
}

Mesh::Mesh(const Mesh& mesh){
    vertices = mesh.vertices;
    indices = mesh.indices;

    initBuffers();
}

Mesh::~Mesh() {
    delete vao;

    delete vbo;
    delete ebo;
}

void Mesh::initBuffers(){
    vao = new VAO();

    vbo = new VBO(&vertices);
    ebo = new EBO(&indices);

    vao->bindBuffers(*vbo, *ebo);
}

const std::vector<GLfloat> Mesh::getVertices() const{
    return this->vertices;
}

void Mesh::draw(const Program& program){
    program.use();

    vao->bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao->unbind();
}

Mesh& Mesh::operator=(const Mesh& other){
    vertices = other.vertices;
    indices = other.indices;
    initBuffers();

    return *this;
}