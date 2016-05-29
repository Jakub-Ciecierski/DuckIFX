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
           vector <GLuint>& indices) :
        vertices(vertices), indices(indices){
    checkError();

    computeTangetBasis();
    initBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertices,
           vector <GLuint>& indices,
           vector<Texture>& textures) :
        vertices(vertices), indices(indices), textures(textures){
    checkError();


    computeTangetBasis();
    initBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertices,
           vector <GLuint>& indices,
           vector<Texture>& textures,
           Material material) :
        vertices(vertices), indices(indices), textures(textures),
        material(material){
    checkError();

    computeTangetBasis();
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

void Mesh::computeTangetBasis(){
    const int DATA_PER_FACE = 3;
    int faceCount = indices.size() / DATA_PER_FACE;
    int vertexIndex = 0;
    std::cout << "Index count: " << indices.size() << std::endl;

    for(int i = 0; i < faceCount; i++){
        if(i ==2 ){
            std::cout << "Index count: " << indices.size() << std::endl;
        }
        if(vertexIndex >= indices.size()){
            throw new std::invalid_argument("computeTangetBasis out of bounds");
        }
        computeAndStoreTangetBasis(vertices[indices[vertexIndex+0]],
                                   vertices[indices[vertexIndex+1]],
                                   vertices[indices[vertexIndex+2]]);

        std::cout << "Face[" << i << "]" << std::endl;
        std::cout << "V0: " << vertexIndex+0 << std::endl;
        std::cout << "V1: " << vertexIndex+1 << std::endl;
        std::cout << "V2: " << vertexIndex+2 << std::endl << std::endl;
        vertexIndex += DATA_PER_FACE;

    }
}

void Mesh::computeAndStoreTangetBasis(Vertex& v0, Vertex& v1, Vertex& v2){
    glm::vec3 P = v1.Position - v0.Position;
    glm::vec3 Q = v2.Position - v0.Position;

    float s1 = v1.TexCoords.x - v0.TexCoords.x;
    float t1 = v1.TexCoords.y - v0.TexCoords.y;

    float s2 = v2.TexCoords.x - v0.TexCoords.x;
    float t2 = v2.TexCoords.x - v0.TexCoords.x;

    float tmp = 1.0f;
    float diff = s1*t2 - s2*t1;
    float errTol = 0.0001;
    if(fabsf(diff) >= errTol){
        tmp = 1.0f / diff;
    }
    tmp = 1.0f / diff;
    glm::vec3 tanget = glm::vec3(t2*P.x - t1*Q.x,
                                 t2*P.y - t1*Q.y,
                                 t2*P.z - t1*Q.z);
    tanget *= tmp;

    glm::vec3 binormal = glm::vec3(s1*Q.x - s2*P.x,
                                   s1*Q.y - s2*P.y,
                                   s1*Q.z - s2*P.z);
    binormal *= tmp;

    tanget = glm::normalize(tanget);
    binormal = glm::normalize(binormal);

    v0.Tangent = tanget;
    v1.Tangent = tanget;
    v2.Tangent = tanget;

    v0.Binormal = binormal;
    v1.Binormal = binormal;
    v2.Binormal = binormal;

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
        }else if(textures[i].texType == TextureTypes::NORMAL){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             MATERIAL_NORMAL_NAME.c_str()),i);
        }else if(textures[i].texType == TextureTypes::CUBEMAP){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             TEXTURE_CUBEMAP_NAME.c_str()),i);
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
    int normalTexCount = 0;
    for(unsigned int i = 0; i < textures.size(); i++){
        if(textures[i].texType == TextureTypes::DIFFUSE)
            diffuseTexCount++;
        if(textures[i].texType == TextureTypes::SPECULAR)
            specularTexCount++;
        if(textures[i].texType == TextureTypes::NORMAL)
            normalTexCount++;
    }

    str += "Vertices Count:          " + to_string(vertices.size()) + "\n";
    str += "Texture Diffuse Count:   " + to_string(diffuseTexCount) + "\n";
    str += "Texture Specular Count:  " + to_string(specularTexCount) + "\n";
    str += "Texture Normal Count:  " + to_string(normalTexCount) + "\n";

    return str;
}