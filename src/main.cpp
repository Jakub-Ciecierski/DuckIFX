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
#include <light_loader.h>
#include <lighting/light_group.h>
#include "camera_controls.h"
#include "window.h"
#include "shaders/loaders/program_loader.h"

using namespace std;

// ------------------------------

int width;
int height;

ifc::Window* window;

Camera* camera;
CameraControls * controls;

RenderObjectLoader* renderObjectLoader;
RenderObject* squareObjectLight1;
RenderObject* squareObjectLight2;
RenderObject* squareObjectLight3;

const int BOXES_COUNT = 10;
RenderObject* boxes[BOXES_COUNT];

LightLoader lightLoader;

LightGroup lightGroup;

LightPoint* lightPoint1;
LightPoint* lightPoint2;
LightPoint* lightPoint3;
LightDirectional* lightDirectional;
LightSpotlight* lightSpotlight;

ProgramLoader programLoader;
Program* programAllLight;
Program* programDirLight;
Program* programFlashlight;
Program* programGlobalLight;
Program* programGlobalAttenuationLight;
Program* programLamp;

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
    camera = new Camera(&width, &height);
    camera->moveTo(glm::vec3(-1.5f, 0.8f, 0.0f));

    controls = new CameraControls(camera);

    initShaders();
    initExampleMeshes();
}

void initExampleMeshes(){
    renderObjectLoader = new RenderObjectLoader();

    squareObjectLight1 = renderObjectLoader->loadLampObject();
    squareObjectLight2 = renderObjectLoader->loadLampObject();
    squareObjectLight3 = renderObjectLoader->loadLampObject();

    // ------

    lightPoint1 = lightLoader.loadPointLight();
    lightPoint2 = lightLoader.loadPointLight();
    lightPoint3 = lightLoader.loadPointLight();
    lightDirectional = lightLoader.loadDirLight();
    lightSpotlight = lightLoader.loadSpotlight();

    lightPoint1->setRenderObject(squareObjectLight1);
    lightPoint2->setRenderObject(squareObjectLight2);
    lightPoint3->setRenderObject(squareObjectLight3);

    lightSpotlight->setCamera(camera);
    // -------

    //lightGroup.addLightDirectional(lightDirectional);
    lightGroup.addLightSpotlight(lightSpotlight);
    lightGroup.addLightPoint(lightPoint1);
    lightGroup.addLightPoint(lightPoint2);
    lightGroup.addLightPoint(lightPoint3);

    squareObjectLight1->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    squareObjectLight2->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    squareObjectLight3->scale(glm::vec3(0.3f, 0.3f, 0.3f));

    squareObjectLight1->moveTo(glm::vec3(2.0f, 2.0f, 2.0f));
    squareObjectLight1->moveTo(glm::vec3(0.0f, 5.0f, 0.0f));

    int MAX = 5;
    float min = 2.5f;
    for(int i = 0; i < BOXES_COUNT; i++){
        float x =
                static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/MAX));
        float y =
                static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/MAX));
        float z =
                static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/MAX));

        boxes[i] = renderObjectLoader->loadCubeObject();
        boxes[i]->moveTo(glm::vec3(x - min, y - min, z - min));
    }
}

void initShaders(){
    programAllLight = programLoader.loadAllLightProgram();

    programGlobalLight = programLoader.loadGlobalLightProgram();
    programGlobalAttenuationLight
            = programLoader.loadGlobalAttenuationLightProgram();

    programDirLight = programLoader.loadDirectionalLightProgram();
    programFlashlight = programLoader.loadFlashlightProgram();

    programLamp = programLoader.loadLampProgram();
}

void releaseResources(){
    delete window;

    delete programAllLight;
    delete programGlobalLight;
    delete programGlobalAttenuationLight;
    delete programDirLight;
    delete programFlashlight;
    delete programLamp;

    delete renderObjectLoader;
    delete squareObjectLight1;
    delete squareObjectLight2;
    delete squareObjectLight3;

    for(int i = 0; i < BOXES_COUNT; i++){
        delete boxes[i];
    }
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

    for(int i = 0; i < BOXES_COUNT; i++){
        boxes[i]->update();
    }
    squareObjectLight1->update();
    squareObjectLight2->update();
    squareObjectLight3->update();

    // ------------------
    static float a = 0;
    float radius = 4.0f;
    squareObjectLight1->moveTo(glm::vec3(cos(a)*radius,
                                         sin(a)*radius, 0.0f));
    squareObjectLight2->moveTo(glm::vec3(cos(a)*radius,
                                         0.0f, sin(a)*radius));
    squareObjectLight3->moveTo(glm::vec3(0.0f, cos(a)*radius,
                                         sin(a)*radius));
    a+=0.005f;
    if(a > 360) a = 0;
    // ------------------
}
void render(){
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->use(*programAllLight);
    lightGroup.use(*programAllLight);

    for(int i = 0; i < BOXES_COUNT; i++){
        boxes[i]->render(*programAllLight);
    }

    camera->use(*programLamp);
    squareObjectLight1->render(*programLamp);
    squareObjectLight2->render(*programLamp);
    squareObjectLight3->render(*programLamp);
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