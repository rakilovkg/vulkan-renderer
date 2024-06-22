#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WINDOW_WIDTH = 512;
const uint32_t WINDOW_HEIGHT = 512;

class Application {
public:
  void run() {
	initializeWindow();
	initializeVulkan();
	runMainLoop();
	cleanup();
  }

private:
  void initializeWindow() {
    glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan Application", nullptr, nullptr);
  }
  
  void initializeVulkan() {
	  
  }
  
  void runMainLoop() {
	while (!glfwWindowShouldClose(window)) {
	  glfwPollEvents();
	}
  }
  
  void cleanup() {
	glfwDestroyWindow(window);
	glfwTerminate();
  }
  
  GLFWwindow *window;
};

int main(int argc, char *argv[]) {
  Application application;
  try {
	application.run();
  } catch (const std::excepttion& exception) {
	std::cerr << exception.what() << std::endl;
	return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}