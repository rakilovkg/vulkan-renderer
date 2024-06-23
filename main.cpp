#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <vector>

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
	createInstance();
  }
  
  void createInstance() {
	VkApplicationInfo applicationInfo{};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pApplicationName = "Vulkan App";
	applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName = "No Engine";
	applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.apiVersion = VK_VERSION_1_0;
	  
	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	
	instanceCreateInfo.enabledLayerCount = 0;
	
	uint32_t glfwExtensionCount = 0;
	const char **glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	
	std::vector<const char*> requiredExtensions;
	
	for (uint32_t i = 0; i < glfwExtensionCount; i++) {
		requiredExtensions.emplace_back(glfwExtensions[i]);
	}
	
	/*
	-- MacOS --
	requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	instanceCreateInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
	*/
	instanceCreateInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
	instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
	
	if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create Vulkan instance.");
	}

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "Available extensions:" << std::endl;
	for (const auto& extension : extensions) {
	  std::cout << extension.extensionName << std::endl;
	}
  }
  
  void runMainLoop() {
	while (!glfwWindowShouldClose(window)) {
	  glfwPollEvents();
	}
  }
  
  void cleanup() {
	vkDestroyInstance(instance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
  }
  
  GLFWwindow *window;
  VkInstance instance;
};

int main(int argc, char *argv[]) {
  Application application;
  try {
	application.run();
  } catch (const std::exception& exception) {
	std::cerr << exception.what() << std::endl;
	return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}