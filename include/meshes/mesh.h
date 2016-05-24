//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_MESH_H
#define DUCK_MESH_H


#include "shaders/program.h"
#include "buffers/vbo.h"
#include "buffers/vao.h"

#include <GL/gl.h>
#include <vector>

class Mesh {
private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    VAO* vao;
    VBO* vbo;
    EBO* ebo;

    void initBuffers();
public:

    Mesh();
    Mesh(std::vector<GLfloat>& vertices,
         std::vector <GLuint>& indices);
    Mesh(const Mesh& mesh);

    ~Mesh();

    const std::vector<GLfloat> getVertices() const;

    void draw(const Program& program);

    Mesh& operator=(const Mesh& other);
};


#endif //DUCK_MESH_H
