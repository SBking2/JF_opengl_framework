#include <iostream>
#include <memory>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Application/Application.h"

int main()
{
    std::shared_ptr<JF::Application> application = std::make_shared<JF::Application>();
    while (!glfwWindowShouldClose(application->get_window()->get_glfw_window())) {
        application->on_render();
        application->on_update();
    }
    glfwTerminate();
    return 0;
}
