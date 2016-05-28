//
// Created by jakub on 5/24/16.
//

#ifndef DUCK_MESH_H
#define DUCK_MESH_H


#include "shaders/program.h"
#include "buffers/vbo.h"
#include "buffers/vao.h"
#include "mesh_data.h"

#include <GL/gl.h>
#include <vector>

/*
 * Contains the geometry of an object.
 * Vertices, indices, textures and material is defined.
 *
 * One instance of the same Mesh should be present in the system.
 * Use Multiple RenderObjects to bind the same Mesh
 */
class Mesh {
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Material material;

    VAO* vao;
    VBO* vbo;
    EBO* ebo;

    /*
     * Checks for errors in the Mesh class and throws exceptions;
     */
    void checkError();

    /*
     * Copy contructor/operator=
     */
    void copy(const Mesh& other);

    void initBuffers();

    /*
     * Binds all textures during draw operation
     */
    void bindTextures(const Program& program);
    void bindColor(const Program& program);
public:

    Mesh();
    Mesh(std::vector<Vertex> vertices,
         std::vector <GLuint>& indices);

    Mesh(std::vector<Vertex> vertices,
         std::vector <GLuint>& indices,
         std::vector<Texture>& textures);

    Mesh(std::vector<Vertex> vertices,
         std::vector <GLuint>& indices,
         std::vector<Texture>& textures,
         Material material);

    Mesh(const Mesh& mesh);

    ~Mesh();

    void setMaterial(const Material& material);

    void draw(const Program& program);

    Mesh& operator=(const Mesh& other);
};


#endif //DUCK_MESH_H
