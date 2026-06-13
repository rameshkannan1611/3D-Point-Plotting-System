#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);
void processinput(GLFWwindow* pWindow);

int main()
{
	//glm test
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f); //identy matrix
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
	vec = trans * vec;
	std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;

	std::cout << "Helo World";

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* pWindow1 = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

	if (!pWindow1)
	{
		std::cout << "Could not create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pWindow1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(pWindow1, framebuffer_size_callback);

	while (!glfwWindowShouldClose(pWindow1))
	{
		processinput(pWindow1);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(pWindow1);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
{
	if (!pWindow)
		return;

	glViewport(0, 0, width, height);

}
void processinput(GLFWwindow* pWindow)
{
	if ((glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS))
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
}
