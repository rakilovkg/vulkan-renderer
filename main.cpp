// g++ main.cpp -o main.exe -Iinclude -Llib -lvulkan-1 -lglfw3 -lgdi32 && main.exe

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
  glfwInit();
  
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow *window = glfwCreateWindow(512, 512, "Моя супер гра!", nullptr, nullptr);
  
  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  std::cout << "extension count: " << extensionCount << std::endl;
  
  glm::mat4 matrix;
  glm::vec4 vector;
  auto test = matrix * vector;
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}