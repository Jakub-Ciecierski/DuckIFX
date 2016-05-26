//
// Created by jakub on 5/23/16.
//

#ifndef DUCK_WINDOW_H
#define DUCK_WINDOW_H

#include <string>
#include <GLFW/glfw3.h>
namespace ifc {
    class Window {
    private:
        GLFWwindow *glfwWindow;

        int width;
        int height;
        std::string name;

        void init();
        void setViewport();

    public:

        Window(int width, int height, std::string name);
        ~Window();

        int shouldClose();
        void update();

        GLFWwindow* getHandle();

    };
}

#endif //DUCK_WINDOW_H
