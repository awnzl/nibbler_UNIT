#ifndef __GLFWWRAPPER_H
# define __GLFWWRAPPER_H

#include <iostream>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "defines.h"
#include "guidisplay.h"

class GLFWWrapper : public GUIDisplay {
    GLFWwindow *win;

    GLFWWrapper(GLFWWrapper const &) = delete;
    GLFWWrapper(GLFWWrapper &&) = delete;
    GLFWWrapper &operator=(GLFWWrapper &) = delete;
    GLFWWrapper &operator=(GLFWWrapper &&) = delete;

    int     m_width;
    int     m_height;

public:
    // GLFWWrapper();
    GLFWWrapper(int width, int height);
    ~GLFWWrapper();

    void    render(uint8_t *rawImage) override;
    int     getEvent() override;
};

#endif