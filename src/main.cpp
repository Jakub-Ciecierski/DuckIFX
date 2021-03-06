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
#include <textures/texture_loader.h>
#include <duck/duck_path.h>
#include <mesh/Water.h>
#include "camera_controls.h"
#include "window.h"
#include "shaders/loaders/program_loader.h"

using namespace std;


// ------------------------------

float lastTick;

int width;
int height;

ifc::Window* window;

Camera* camera;
CameraControls * controls;

DuckPath* duckPath;

RenderObjectLoader* renderObjectLoader;
RenderObject* planeObject;
RenderObject* duckObject;
RenderObject* nanoSuitObject;
RenderObject* cubeMapObject;
RenderObject* box;
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
Program* programCubemap;
Program* programBumpMap;
Program* programLight;
Program* programAnisLight;
Program* programLamp;

const int x = 400;
const int y = 400;
const float unit = 0.01f;

Water* water;

const int textureDataWidth = x;
const int textureDataHeight = y;
Texture normalTexture;
unsigned char* textureDataChar;

void initTextureData();
void deleteTextureData();
void updataTextureData(Texture& texture, GLubyte value);


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
    initTextureData();
    initScene();

    mainLoop();

    releaseResources();
    deleteTextureData();

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

    lastTick = glfwGetTime();
}

void initExampleMeshes(){
    renderObjectLoader = new RenderObjectLoader();

    planeObject = renderObjectLoader->loadPlaneObject();
    Mesh* mesh = planeObject->getModel()->getMesh(0);
    mesh->addTexture(normalTexture);

    water = new Water(x, y, unit, planeObject);
    //water->NewRipple(100, 100);

    cubeMapObject = renderObjectLoader->loadCubemapObject();

    nanoSuitObject = renderObjectLoader->loadnanosuitObject();
    squareObjectLight1 = renderObjectLoader->loadLampObject();
    squareObjectLight2 = renderObjectLoader->loadLampObject();
    squareObjectLight3 = renderObjectLoader->loadLampObject();

    duckObject = renderObjectLoader->loadDuckObject();
    duckPath = new DuckPath(duckObject, -10, 10, -10, 10, 0);

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

    //lightGroup.addLightSpotlight(lightSpotlight);
    lightGroup.addLightDirectional(lightDirectional);
    //lightGroup.addLightPoint(lightPoint1);
    //lightGroup.addLightPoint(lightPoint2);
    //lightGroup.addLightPoint(lightPoint3);
    // -------

    nanoSuitObject->scale(glm::vec3(0.2f, 0.2f, 0.2f));
    nanoSuitObject->moveTo(glm::vec3(0.0, -1.0f, 0.0f));

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
    programCubemap = programLoader.loadCubemapProgram();

    programBumpMap = programLoader.loadBumpMappingProgram();
    programLight = programLoader.loadAllLightProgram();

    programLamp = programLoader.loadLampProgram();

    programAnisLight = programLoader.loadAnisotropicLightProgram();
}

void releaseResources(){
    delete window;


    delete programCubemap;
    delete programBumpMap;
    delete programLight;
    delete programLamp;
    delete programAnisLight;

    delete duckPath;

    delete renderObjectLoader;
    delete planeObject;
    delete water;
    delete duckObject;
    delete squareObjectLight1;
    delete squareObjectLight2;
    delete squareObjectLight3;
    delete cubeMapObject;

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

    squareObjectLight1->update();
    cubeMapObject->update();
    duckObject->update();
    water->Update();

    //  MOVE DUCK ------------------
    float tick = glfwGetTime();
    float dt = tick - lastTick;
    lastTick = tick;
    duckObject->moveTo(duckPath->computePosition(dt));
    // ------------------

    // MOVE LIGHT ------------------
    static float a = 0;
    float radius = 4.0f;
    squareObjectLight1->moveTo(glm::vec3(cos(a)*radius,
                                         sin(a)*radius, 0.0f));
    a+=0.005f;
    if(a > 360) a = 0;
    // ------------------

    updataTextureData(normalTexture, a);
}

void render(){
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    camera->use(*programBumpMap);
    lightGroup.use(*programBumpMap);
    duckObject->render(*programBumpMap);
*/
    // Draw Scene

    Program* program = programLight;
    //Program* program = programAnisLight;
    camera->use(*program);
    lightGroup.use(*program);
    duckObject->render(*program);


    // Draw Lamp
    camera->use(*programLamp);
    lightGroup.render(*programLamp);

    // Draw Cubemap
    glEnable(GL_CULL_FACE);
    camera->use(*programCubemap);
    cubeMapObject->render(*programCubemap);
    glDisable(GL_CULL_FACE);

    camera->use(*programBumpMap);
    lightGroup.use(*programBumpMap);
    water->Render(*programBumpMap);
}

void mainLoop(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(!window->shouldClose())
    {
        update();
        render();

        glfwSwapBuffers(window->getHandle());
    }
    glfwTerminate();
}

// Texture ---------------------------

void initTextureData(){
    int count = textureDataWidth*textureDataHeight*3;
    int pixelCount = count / 3;
    textureDataChar = new unsigned char[count];

    int index = 0;
    for(int i = 0; i < pixelCount; i++){
        textureDataChar[index]      = 0;
        textureDataChar[index + 1]  = 255;
        textureDataChar[index + 2]  = 0;
        index += 3;
    }

    TextureLoader loader;
    normalTexture = loader.loadFromData(TextureTypes::NORMAL, textureDataChar,
                                        textureDataWidth, textureDataHeight);
}

void deleteTextureData(){
    delete textureDataChar;
}

void updataTextureData(Texture& texture, GLubyte value){
    int count = textureDataWidth*textureDataHeight*3;
    int pixelCount = count / 3;
    int pixelIndex = 0;

    float min = -1;
    float max = 1;

    int maxByte = 255;
    int minByte = 0;

    const vector<vector<glm::vec3>>&normals = water->getNormals();
    static int a = 0;
    a++;
    if(a > 255) a = 0;
    for(unsigned int i = 0; i < normals.size(); i++){
        vector<glm::vec3> vec = normals[i];
        for(unsigned int j = 0; j < vec.size(); j++){
            /*
            if(vec[j].y == 0 && vec[j].x == 0 && vec[j].z == 0){
                vec[j].x = 0;
                vec[j].y = 1;
                vec[j].z = 0;
            }
            if(isnan(vec[j].x) || isnan(vec[j].y) || isnan(vec[j].z)){
                vec[j].x = 0;
                vec[j].y = 1;
                vec[j].z = 0;
            }*/
            /*
            if(vec[j].y != 1){
                std::cout << vec[j].x << ", " <<  vec[j].y << ", " << vec[j].z
                << std::endl;
            }
*/

            float xNorm = (vec[j].x - min) / (max - min);
            float yNorm = (vec[j].y - min) / (max - min);
            float zNorm = (vec[j].z - min) / (max - min);
            unsigned char xByte;
            unsigned char yByte;
            unsigned char zByte;

            xByte = maxByte * xNorm;
            yByte = maxByte * yNorm;
            zByte = maxByte * zNorm;

            textureDataChar[pixelIndex]      = xByte;
            textureDataChar[pixelIndex + 1]  = yByte;
            textureDataChar[pixelIndex + 2]  = zByte;

            pixelIndex += 3;
        }
    }

    texture.updateData(textureDataChar, textureDataWidth,
                       textureDataHeight, 3);
}
