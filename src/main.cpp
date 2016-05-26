#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <shaders/loaders/shader_loader.h>
#include <cmath>
#include <shaders/program.h>
#include <render_object.h>
#include <render_object_loader.h>
#include "window.h"

using namespace std;

// ------------------------------

ifc::Window* window;


RenderObjectLoader* renderObjectLoader;
RenderObject* squareObject;
RenderObject* triangleObject;

Program* program;

// ------------------------------
MeshLoader meshLoader;
Mesh sqaureMesh;
Mesh triangleMesh;

void initContext();
void initRenderContext();
void initOpenGLContext();
void initCallbacks();

void initScene();
void initExampleMeshes();
void initShaders();

void releaseResources();

void key_callback(GLFWwindow* window, int key,
                  int scancode, int action, int mode);

void mainLoop();
// ------------------------------

int main() {
    initContext();
    initScene();

    mainLoop();

    releaseResources();

    return 0;
}
void initContext(){
    initRenderContext();
    window = new ifc::Window(800, 600, "Duck");
    initOpenGLContext();
    initCallbacks();
}

void initRenderContext(){
    glfwInit();
    // OpenGL version required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // No legacy functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void initOpenGLContext(){
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        throw new std::invalid_argument("Failed to initialize GLEW");
    }
}

void initCallbacks(){
    glfwSetKeyCallback(window->getHandle(), key_callback);
}


void initScene(){
    initShaders();
    initExampleMeshes();
}

void initExampleMeshes(){
    renderObjectLoader = new RenderObjectLoader();

    squareObject = renderObjectLoader->loadSqaureObject();
    triangleObject = renderObjectLoader->loadTriangleObject();
}

void initShaders(){
    ShaderLoader shaderLoader;

    VertexShader vertexShader =
            shaderLoader.loadVertexShader("res/shaders/tex_vert.glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader("res/shaders/tex_frag.glsl");

    fragmentShader.compile();
    vertexShader.compile();

    program = new Program(vertexShader, fragmentShader);
}

void releaseResources(){
    delete window;
    delete program;

    delete renderObjectLoader;
    delete squareObject;
    delete triangleObject;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void mainLoop(){
    float x = 0.01;
    while(!window->shouldClose())
    {
        window->update();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        triangleObject->update();
        squareObject->update();

        squareObject->render(*program);
        triangleObject->render(*program);

        glfwSwapBuffers(window->getHandle());
    }
    glfwTerminate();
}