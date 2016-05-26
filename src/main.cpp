#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <shaders/loaders/shader_loader.h>
#include <cmath>
#include <shaders/program.h>
#include <render_object.h>
#include <render_object_loader.h>
#include <camera.h>
#include <lighting/light_source.h>
#include "camera_controls.h"
#include "window.h"

using namespace std;

// ------------------------------

int width;
int height;

ifc::Window* window;

Camera* camera;
CameraControls * controls;

RenderObjectLoader* renderObjectLoader;
RenderObject* squareObject;
RenderObject* squareObjectLight;

LightSource* lightSource;

Program* program;
Program* programLight;

// ------------------------------

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
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window,
                           int button, int action, int mods);

void mainLoop();

void update();
void render();

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

    width = 800;
    height = 600;
    window = new ifc::Window(width, height, "Duck");

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
    glfwSetCursorPosCallback(window->getHandle(), mouse_callback);
    glfwSetMouseButtonCallback(window->getHandle(), mouse_button_callback);
}


void initScene(){
    initShaders();
    initExampleMeshes();

    camera = new Camera(&width, &height);
    camera->moveTo(glm::vec3(-1.5f, 0.8f, 0.0f));

    controls = new CameraControls(camera);
}

void initExampleMeshes(){
    renderObjectLoader = new RenderObjectLoader();

    squareObject = renderObjectLoader->loadCubeObject();
    squareObjectLight = renderObjectLoader->loadLampObject();

    lightSource = new LightSource(squareObjectLight);
    Light light;
    light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular= glm::vec3(1.0f, 1.0f, 1.0f);
    lightSource->setLight(light);

    squareObjectLight->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    squareObjectLight->moveTo(glm::vec3(2.0f, 2.0f, 2.0f));
    squareObjectLight->moveTo(glm::vec3(0.0f, 5.0f, 0.0f));
}

void initShaders(){
    ShaderLoader shaderLoader;

    VertexShader vertexShader =
            shaderLoader.loadVertexShader("res/shaders/lighting/mat_vert"
                                                  ".glsl");
    FragmentShader fragmentShader =
            shaderLoader.loadFragmentShader("res/shaders/lighting/mat_frag"
                                                    ".glsl");

    vertexShader.compile();
    fragmentShader.compile();

    program = new Program(vertexShader, fragmentShader);

    VertexShader vertexShaderLight =
            shaderLoader.loadVertexShader("res/shaders/lighting/light_src_vert"
                                                  ".glsl");
    FragmentShader fragmentShaderLight =
            shaderLoader.loadFragmentShader
                    ("res/shaders/lighting/light_src_frag"
                                                    ".glsl");
    vertexShaderLight.compile();
    fragmentShaderLight.compile();

    programLight = new Program(vertexShaderLight, fragmentShaderLight);
}

void releaseResources(){
    delete window;
    delete program;
    delete programLight;

    delete renderObjectLoader;
    delete squareObject;
    delete squareObjectLight;

    delete lightSource;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    controls->onKeyboardAction(action, key);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    controls->onMouseAction(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window,
                           int button, int action, int mods){
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if(state == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        controls->setMousePress(true);
        controls->setPressedPosition(xpos, ypos);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }else if(state == GLFW_RELEASE){
        controls->setMousePress(false);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void update(){
    window->update();

    controls->doMovement();
    camera->update();

    squareObjectLight->update();
    squareObject->update();

    static float a = 0;

    squareObjectLight->moveTo(glm::vec3(cos(a)*2, sin(a)*2, 0.0f));
    a+=0.005f;
    if(a > 360) a = 0;
}
void render(){
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->use(*program);
    lightSource->use(*program);

    squareObject->render(*program);

    camera->use(*programLight);
    lightSource->render(*programLight);
}

void mainLoop(){
    glEnable(GL_DEPTH_TEST);

    while(!window->shouldClose())
    {
        update();
        render();

        glfwSwapBuffers(window->getHandle());
    }
    glfwTerminate();
}