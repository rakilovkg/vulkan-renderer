#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class Application {
public:
  void run() {
	initializeVulkan();
	runMainLoop();
	cleanup();
  }

private:
  void initializeVulkan() {
  }
  
  void runMainLoop() {
	
  }
  
  void cleanup() {
	
  }
  
  VkInstance vkInstance;
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