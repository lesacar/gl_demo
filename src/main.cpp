#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW to use OpenGL 3.3 core profile (my gpu only supports up to 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the context current
    glfwMakeContextCurrent(window);
	glfwSwapInterval(0); // ask GPU to disable vsync
    // Load OpenGL functions using Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize Glad" << std::endl;
        return -1;
    }

    // Get GPU information
    const char* gpuName = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* gpuVendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const char* gpuVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Print GPU information
    std::cout << "GPU Name: " << gpuName << std::endl;
    std::cout << "GPU Vendor: " << gpuVendor << std::endl;
    std::cout << "OpenGL Version: " << gpuVersion << std::endl;

    // FPS calculation variables
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    while (!glfwWindowShouldClose(window)) {
        // Measure time
        double currentTime = glfwGetTime();
        nbFrames++;

        // If a second has passed
        if (currentTime - lastTime >= 1.0) {
            // Print FPS
            std::cout << "FPS: " << nbFrames << std::endl;
            nbFrames = 0;
            lastTime += 1.0;
        }

        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

